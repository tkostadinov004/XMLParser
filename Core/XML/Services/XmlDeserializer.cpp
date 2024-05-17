#include "XmlDeserializer.h"
#include "../Models/XMLTextNode.h"
#include "../../../Utils/Exceptions/FileError.h"
#include "..\..\..\Utils\MyStack\MyStack.hpp"

static bool isWhitespace(char c)
{
	return c == ' ' || c == '\n' || c == '\t' || c == '\f' || c == '\v' || c == '\r';
}
static bool isTerminator(char c)
{
	return c == '>';
}
static void skipWhitespace(std::istream& is)
{
	char c = is.get();
	while (isWhitespace(c) && !is.eof())
	{
		c = is.get();
	}
	is.seekg(-1, std::ios::cur);
}
static MyString takeWhile(std::istream& is, bool(*pred)(char))
{
	MyString result;
	is.seekg(-1, std::ios::cur);
	while (pred(is.peek()) && !is.eof())
	{
		result += is.get();
	}
	return result;
}

XMLAttribute XmlDeserializer::deserializeAttribute(const MyString& arg)
{
	XMLAttribute result;
	MyVector<MyString> splitted = arg.split('=');
	result.setKey(splitted[0]);
	result.setValue(splitted[1].skipWhile([](char c) {return c == '\"';}).takeWhile([](char c) {return c != '\"';}));

	return result;
}

MyVector<XMLAttribute> XmlDeserializer::deserializeAttributes(std::istream& is)
{
	return MyVector<XMLAttribute>();
}

XmlDeserializer::XmlDeserializer(const MyString& path)
{
	setWorkingPath(path);
}

XMLDocument XmlDeserializer::deserialize()
{
	std::ifstream ifs(_path.c_str(), std::ios::in | std::ios::out);
	if (!ifs.is_open())
	{
		throw FileError("Unable to open or create file!");
	}

	XMLDocument result;
	bool isRootSet = false;

	XMLElementNode* previousParent = &result.root();
	State state = State::Initial;
	MyString currentTagName;
	MyString currentPlainText;

	XMLElementNode current;
	MyStack<MyString> tags;
	while (!ifs.eof())
	{		
		char c = ifs.get();
		if (c == '<')
		{
			state = State::StartOfTag;
		}
		else if (state == State::StartOfTag)
		{
			if (c == '/')
			{
				state = State::StartOfClosingTag;
				continue;
			}
			state = State::CurrentlyReadingTag;
			currentTagName += c;
		}
		else if (state == State::CurrentlyReadingTag)
		{
			currentTagName += takeWhile(ifs, [](char c) {return !isWhitespace(c) && !isTerminator(c);}).trim();
			c = ifs.get();

			current.setParent(previousParent);
			bool isSelfClosing = currentTagName.ends_with("/");
			if (isSelfClosing)
			{
				currentTagName = currentTagName.substr(0, currentTagName.length() - 1);	
			}
			else
			{
				tags.push(currentTagName);
			}
			current.setTagName(currentTagName);
			currentTagName.clear();

			if (isWhitespace(c))
			{
				state = State::CurrentlyReadingAttributes;
				continue;
			}
			else if (isTerminator(c))
			{
				state = State::EndOfTag;
				if (currentTagName.contains(":"))
				{
					MyString nsName = currentTagName.split(':')[0];
					current.assignNamespace(XMLNamespace(nsName, currentTagName.split(':')[1]));
				}
				if (!isRootSet)
				{
					previousParent->setTagName(current.getTagName());
					isRootSet = true;
				}
				else
				{
					XMLElementNode* currentDyn = new XMLElementNode(current);
					previousParent->addChild(currentDyn);
					if (!isSelfClosing)
					{
						previousParent = currentDyn;
					}
					current = XMLElementNode();
				}
				continue;
			}
		}
		else if (state == State::CurrentlyReadingAttributes)
		{
			MyVector<XMLAttribute> attributes =
				takeWhile(ifs, [](char c) {return !isTerminator(c);})
				.trimEnd()
				.split(' ', true)
				.convertTo<XMLAttribute>([this](const MyString& arg) {return deserializeAttribute(arg);});
			current.addAttributes(attributes);
			state = State::EndOfTag;
			c = ifs.get();

			if (current.getTagName().contains(":"))
			{
				MyString nsName = current.getTagName().split(':')[0];
				current.assignNamespace(XMLNamespace(nsName, current.getTagName().split(':')[1]));
			}

			XMLElementNode* currentDyn = new XMLElementNode(current);
			previousParent->addChild(currentDyn);
			previousParent = currentDyn;
			current = XMLElementNode();
		}
		else if ((state == State::EndOfTag || state == State::Initial) && !isWhitespace(c) && c != '<' && c != '>')
		{
			state = State::CurrentlyReadingPlainText;
			currentPlainText += c;
		}
		else if (state == State::CurrentlyReadingPlainText && !isWhitespace(c))
		{
			currentPlainText += takeWhile(ifs, [](char c) {return c != '<';}).trim();
			if (!currentPlainText.empty())
			{
				previousParent->addChild(new XMLTextNode(currentPlainText));
				currentPlainText.clear();
			}
			state = State::EndOfPlainText;
		}
		else if (state == State::StartOfClosingTag && c != '<' && !isWhitespace(c))
		{
			currentTagName += takeWhile(ifs, [](char c) {return !isTerminator(c);})
				.trim();
			c = ifs.get();

			if (currentTagName != tags.peek())
			{
				throw std::exception("Opening tag missing!");
			}
			tags.pop();
			currentTagName.clear();

			previousParent = dynamic_cast<XMLElementNode*>(previousParent->parent());
			current = XMLElementNode();
			state = State::Initial;
		}
	}

	if (!tags.empty())
	{
		MyString unclosedTags = join(tags.convertTo<MyString>([](const MyString& tag) {return tag;}), ", ");
		throw std::exception(MyString("Opening tags for: " + unclosedTags + " are not defined!").c_str());
	}
	return result;
}

const MyString& XmlDeserializer::getWorkingPath() const
{
	return _path;
}

void XmlDeserializer::setWorkingPath(const MyString& path)
{
	this->_path = path;
}

