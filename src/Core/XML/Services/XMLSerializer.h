#pragma once
#include "..\..\..\Utils\MyString\MyString.h"
#include "..\Documents\XMLDocument.h"

class XMLSerializer
{
	MyString _path;
public:
	explicit XMLSerializer(const MyString& path);
	void serializeToStream(const XMLDocument& document);
	const MyString& getWorkingPath() const;
	void setWorkingPath(const MyString& path);
};