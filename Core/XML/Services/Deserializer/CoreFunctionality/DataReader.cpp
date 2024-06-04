#include "DataReader.h"
static bool isWhitespace(char c)
{
	return c == ' ' || c == '\n' || c == '\t' || c == '\f' || c == '\v' || c == '\r';
}
static bool isTerminator(char c)
{
	return c == '>';
}

void DataReader::skipWhitespace()
{
	char c = is.get();
	while (isWhitespace(c) && !is.eof())
	{
		c = is.get();
	}
	is.seekg(-1, std::ios::cur);
}
MyString DataReader::takeWhile(bool(*pred)(char))
{
	MyString result;
	is.seekg(-1, std::ios::cur);
	while (pred(is.peek()) && !is.eof())
	{
		result += is.get();
	}
	return result;
}
MyString DataReader::getAttributesString()
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
	return result.trim();
}

DataReader::DataReader(std::istream& stream) : is(stream) {}

MyString DataReader::readTag()
{
	return takeWhile([](char c) {return !isWhitespace(c) && !isTerminator(c);}).trim();
}

DeserializedAttribute DataReader::parseAttribute(const MyString& arg)
{
	DeserializedAttribute result;
	MyVector<MyString> splitted = splitAndIgnore(arg, '=', true);

	int namespaceIndex = splitted[0].find(":");
	if (namespaceIndex != -1)
	{
		MyString namespaceName = splitted[0].substr(0, namespaceIndex);
		if (namespaceName == "xmlns")
		{
			result._key = splitted[0];
		}
		else
		{
			MyString tagName = splitted[0].substr(namespaceIndex + 1);
			result._namespaceName = namespaceName;
			result._key = tagName;
		}
	}
	else
	{
		result._key = splitted[0];
	}
	result._value = (splitted[1].skipWhile([](char c) {return c == '\"';}).takeWhile([](char c) {return c != '\"';}));

	return result;
}

AttributeReaderResult DataReader::readAttributes()
{
	AttributeReaderResult result;
	MyString attributeString = getAttributesString().trimEnd();
	result.isTagSelfClosing = attributeString.ends_with("/");
	if (result.isTagSelfClosing)
	{
		attributeString = attributeString.substr(0, attributeString.length() - 1);
	}

	MyVector<DeserializedAttribute> attributes = splitAndIgnore(attributeString).convertTo<DeserializedAttribute>([this](const MyString& attr) {return parseAttribute(attr);});
	for (const DeserializedAttribute& deserializedAttribute : attributes)
	{
		if (deserializedAttribute._key.starts_with("xmlns"))
		{
			result.namespaces.push_back(deserializedAttribute);
		}
		else
		{
			result.attributes.push_back(deserializedAttribute);
		}
	}

	return result;
}

MyString DataReader::readPlainText()
{
	return takeWhile([](char c) {return c != '<';}).trim();
}

MyString DataReader::readClosingTag()
{
	return takeWhile([](char c) {return !isTerminator(c);}).trim();
}
