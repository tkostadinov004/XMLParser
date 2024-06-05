#pragma once
#include <fstream>
#include <sstream>
#include "..\../Documents\XMLDocument.h"
#include "..\..\..\../Utils\MyString\MyString.h"

enum class State
{
	Initial,
	StartOfTag,
	CurrentlyReadingTag,
	InComment,
	CurrentlyReadingAttributes,
	CurrentlyReadingPlainText,
	EndOfPlainText,
	EndOfTag,
	StartOfClosingTag
};
class XMLDeserializer
{
	MyString _path;
public:
	explicit XMLDeserializer(const MyString& path);
	XMLDocument deserialize();
	const MyString& getWorkingPath() const;
	void setWorkingPath(const MyString& path);
};