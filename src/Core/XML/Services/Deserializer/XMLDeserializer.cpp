#include "XmlDeserializer.h"
#include "../../Models/XMLTextNode.h"
#include "../../../../Utils/Exceptions/FileError.h"
#include "..\..\..\../Utils\MyStack\MyStack.hpp"
#include "CoreFunctionality\XMLBuildingContext.h"
#include "..\..\..\..\Utils\Messages\ErrorMessageBuilder.h"

static bool isWhitespace(char c)
{
	return c == ' ' || c == '\n' || c == '\t' || c == '\f' || c == '\v' || c == '\r';
}
static bool isTagOpener(char c)
{
	return c == '<';
}
static bool isTagTerminator(char c)
{
	return c == '>';
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
		throw FileError(ErrorMessageBuilder::UNABLE_TO_OPEN_OR_CREATE_FILE());
	}

	State state = State::Initial;

	DataReader reader(ifs);
	XMLBuildingContext context(reader);
	while (ifs.peek() && !ifs.eof())
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
				ifs.seekg(-1, std::ios::cur);
			}
		}
		else if (state == State::CurrentlyReadingTag)
		{
			context.createTag();
			c = ifs.get();

			if (isWhitespace(c))
			{
				state = State::CurrentlyReadingAttributes;
				continue;
			}
			else if (isTagTerminator(c))
			{
				state = State::EndOfTag;
				context.flushElementNode();
				continue;
			}
		}
		else if (state == State::CurrentlyReadingAttributes)
		{
			context.createAttributes();
			state = State::EndOfTag;
			c = ifs.get();

			context.flushElementNode();
		}
		else if ((state == State::EndOfTag || state == State::Initial) && !isWhitespace(c) && !isTagOpener(c) && !isTagTerminator(c))
		{
			state = State::CurrentlyReadingPlainText;
			ifs.seekg(-1, std::ios::cur);
		}
		else if (state == State::CurrentlyReadingPlainText)
		{
			context.createPlainText();
			context.flushTextNode();
			state = State::EndOfPlainText;
		}
		else if (state == State::StartOfClosingTag && !isTagOpener(c) && !isWhitespace(c))
		{
			context.closeTag();
			c = ifs.get();
			state = State::Initial;
		}
	}
	return context.finish();
}

const MyString& XMLDeserializer::getWorkingPath() const
{
	return _path;
}

void XMLDeserializer::setWorkingPath(const MyString& path)
{
	this->_path = path;
}

