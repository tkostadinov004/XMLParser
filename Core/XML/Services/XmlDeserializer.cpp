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
static MyString readAttributes(std::istream& is)
{
	MyString result;
	is.seekg(-1, std::ios::cur);
	bool isInQuotes = false;
	while ((!isTerminator(is.peek()) || isInQuotes) && !is.eof())
	{
		if (is.peek() == '\"')
		{
			isInQuotes = !isInQuotes;
		}
		result += is.get();
	}
	return result;
}
static MyVector<MyString> splitAndIgnore(const MyString& str, char delim = ' ', bool removeEmptyEntries = false)
{
	MyVector<MyString> splitted;
	bool isInQuotes = false;

	MyString temp;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == delim && !isInQuotes)
		{
			if (removeEmptyEntries && temp.empty())
			{
				continue;
			}
			splitted.push_back(temp);
			temp.clear();
		}
		else if (str[i] == '\"')
		{
			isInQuotes = !isInQuotes;
		}
		else
		{
			temp.append(str[i]);
		}
	}
	splitted.push_back(temp);
	return splitted;
}

XMLAttribute XMLDeserializer::deserializeAttribute(const MyString& arg)
{
	XMLAttribute result;
	MyVector<MyString> splitted = arg.split('=');
	result.setKey(splitted[0]);
	result.setValue(splitted[1].skipWhile([](char c) {return c == '\"';}).takeWhile([](char c) {return c != '\"';}));

	return result;
}

MyVector<XMLAttribute> XMLDeserializer::deserializeAttributes(std::istream& is)
{
	return MyVector<XMLAttribute>();
}

XMLDeserializer::XMLDeserializer(const MyString& path)
{
	setWorkingPath(path);
}

XMLDocument XMLDeserializer::deserialize()
{
	std::ifstream ifs(_path.c_str(), std::ios::in | std::ios::out);
	if (!ifs.is_open())
	{
		throw FileError("Unable to open or create file!");
	}

	bool isRootSet = false;

	MySharedPtr<XMLElementNode> root = new XMLElementNode();
	MyWeakPtr<XMLElementNode> previousParent = root;

	State state = State::Initial;
	MyString currentTagName;
	MyString currentPlainText;
	MyString currentNamespaceName;

	XMLElementNode current;
	MyStack<MyString> tags;
	while (!ifs.eof())
	{
		char c = ifs.get();
		if (state == State::InComment)
		{
			if (c == '-')
			{
				if (ifs.get() == '-')
				{
					if (ifs.get() == '>')
					{
						state = State::Initial;
						continue;
					}
					ifs.seekg(-1, std::ios::cur);
				}
				ifs.seekg(-1, std::ios::cur);
			}
		}
		else if (c == '<')
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
			else if (c == '!')
			{
				if (ifs.get() == '-')
				{
					if (ifs.get() == '-')
					{
						state = State::InComment;
						continue;
					}
					ifs.seekg(-1, std::ios::cur);
				}
				ifs.seekg(-1, std::ios::cur);
			}
			else
			{
				state = State::CurrentlyReadingTag;
				currentTagName += c;
			}
		}
		else if (state == State::CurrentlyReadingTag)
		{
			currentTagName += takeWhile(ifs, [](char c) {return !isWhitespace(c) && !isTerminator(c);}).trim();
			c = ifs.get();

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
			if (current.getTagName().contains(":"))
			{
				MyVector<MyString> splittedTag = current.getTagName().split(':');
				if (!current.getNamespace())
				{
					currentNamespaceName = splittedTag[0];
				}
				current.setTagName(splittedTag[1]);
			}

			if (isWhitespace(c))
			{
				state = State::CurrentlyReadingAttributes;
				continue;
			}
			else if (isTerminator(c))
			{
				state = State::EndOfTag;
				if (!isRootSet)
				{
					previousParent->setTagName(current.getTagName());
					isRootSet = true;
				}
				else
				{
					MySharedPtr<XMLElementNode> currentDyn = new XMLElementNode(current);
					currentDyn->setParent(previousParent);
					previousParent->addChild(currentDyn);
					if (!currentNamespaceName.empty())
					{
						current.assignNamespace(currentNamespaceName);
						currentNamespaceName.clear();
					}
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
			MyString attributeString = readAttributes(ifs).trimEnd();
			bool isSelfClosing = attributeString.ends_with("/");
			if (isSelfClosing)
			{
				attributeString = attributeString.substr(0, attributeString.length() - 1);
				tags.pop();
				c = ifs.get();
			}
			MyVector<XMLAttribute> attributes = splitAndIgnore(attributeString)
				.convertTo<XMLAttribute>([this](const MyString& arg) {return deserializeAttribute(arg);});
			current.addAttributes(attributes);
			state = State::EndOfTag;
			c = ifs.get();

			if (!isRootSet)
			{
				current.assignNamespace(currentNamespaceName);
				*previousParent = current;
				current = XMLElementNode();
				isRootSet = true;
				continue;
			}
			MySharedPtr<XMLElementNode> currentDyn = new XMLElementNode(current);
			currentDyn->setParent(previousParent);
			previousParent->addChild(currentDyn);
			if (!currentNamespaceName.empty())
			{
				current.assignNamespace(currentNamespaceName);
				currentNamespaceName.clear();
			}
			previousParent = currentDyn;
			current = XMLElementNode();
		}
		else if ((state == State::EndOfTag || state == State::Initial))
		{
			if (!isWhitespace(c) && c != '<' && c != '>')
			{
				state = State::CurrentlyReadingPlainText;
				currentPlainText += c;
			}
			else if (!currentNamespaceName.empty())
			{
				throw std::exception("Invalid namespace!");
			}
		}
		else if (state == State::CurrentlyReadingPlainText)
		{
			currentPlainText += takeWhile(ifs, [](char c) {return c != '<';});
			currentPlainText = currentPlainText.trim();
			if (!currentPlainText.empty())
			{
				MySharedPtr<XMLTextNode> resultTextNode = new XMLTextNode(currentPlainText);
				resultTextNode->setParent(previousParent);
				previousParent->addChild(resultTextNode);
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

			previousParent = previousParent->parent();
			current = XMLElementNode();
			state = State::Initial;
		}
	}
	if (!tags.empty())
	{
		MyString unclosedTags = join(tags.convertTo<MyString>([](const MyString& tag) {return tag;}), ", ");
		throw std::exception(MyString("Opening tags for: " + unclosedTags + " are not defined!").c_str());
	}
	return XMLDocument(root);
}

const MyString& XMLDeserializer::getWorkingPath() const
{
	return _path;
}

void XMLDeserializer::setWorkingPath(const MyString& path)
{
	this->_path = path;
}

