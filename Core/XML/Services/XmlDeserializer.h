#pragma once
#include <fstream>
#include "..\Models\XMLDocument.h"
#include "..\..\..\Utils\MyString\MyString.h"

enum class State
{
	Initial,
	StartOfTag,
	CurrentlyReadingTag,
	CurrentlyReadingAttributes,
	CurrentlyReadingPlainText,
	EndOfPlainText,
	EndOfTag,
	StartOfClosingTag
};
class XmlDeserializer
{
	MyString _path;
	XMLAttribute deserializeAttribute(const MyString& arg);
	MyVector<XMLAttribute> deserializeAttributes(std::istream& is);
public:
	explicit XmlDeserializer(const MyString& path);
	XMLDocument deserialize();
	const MyString& getWorkingPath() const;
	void setWorkingPath(const MyString& path);
};