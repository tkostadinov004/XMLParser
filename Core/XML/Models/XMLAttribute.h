#pragma once
#include "../../../Utils/MyString/MyString.h"
class XMLAttribute
{
	MyString _key;
	MyString _value;
public:
	XMLAttribute() = default;
	XMLAttribute(const MyString& key, const MyString& value);
	virtual ~XMLAttribute() = default;

	const MyString& getKey() const;
	const MyString& getValue() const;

	void setKey(const MyString& key);
	void setValue(const MyString& value);
};