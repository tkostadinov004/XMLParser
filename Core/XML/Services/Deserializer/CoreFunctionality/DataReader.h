#pragma once
#include <istream>
#include "../../../../../Utils/MyString/MyString.h"
struct DeserializedAttribute
{
	MyString _key, _value, _namespaceName;
};
struct AttributeReaderResult
{
	MyVector<DeserializedAttribute> namespaces;
	MyVector<DeserializedAttribute> attributes;
	bool isTagSelfClosing = false;
};
class DataReader
{
	std::istream& is;

	MyVector<MyString> splitAndIgnore(const MyString& str, char delim = ' ', bool removeEmptyEntries = false);
	void skipWhitespace();
	MyString takeWhile(bool(*pred)(char));
	MyString getAttributesString();
	DeserializedAttribute parseAttribute(const MyString& arg);
public:
	DataReader(std::istream& stream);
	MyString readTag();
	AttributeReaderResult readAttributes();
	MyString readPlainText();
	MyString readClosingTag();
};