#pragma once
#include "../../../Utils/MyString/MyString.h"
class XMLNamespace
{
	MyString _name;
	MyString _value;
public:
	XMLNamespace() = default;
	XMLNamespace(const MyString& name, const MyString& value);
	const MyString& getName() const;
	void setName(const MyString& name);
	const MyString& getValue() const;
	void setValue(const MyString& value);
};