#pragma once
#include "..\..\..\Utils\MyString\MyString.h"
#include "..\Models\XMLDocument.h"

class XMLSerializer
{
	MyString _path;
public:
	explicit XMLSerializer(const MyString& path);
	void serialize(const XMLDocument& document);
	const MyString& getWorkingPath() const;
	void setWorkingPath(const MyString& path);
};