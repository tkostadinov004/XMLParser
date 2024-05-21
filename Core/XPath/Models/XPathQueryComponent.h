#pragma once
#include "..\..\..\Utils\MyString\MyString.h"
struct AttributeFilter
{
	MyString _key;
	MyString _value;
};
class XPathQueryComponent
{
	MyString _axis = "child";
	MyString _tag;
	int _index = -1;
	AttributeFilter _attributeFilter;
	MyString _attributeExists;
public:
	const MyString& getAxis() const;
	void setAxis(const MyString& axis);
	const MyString& getTag() const;
	void setTag(const MyString& tag);
	int getIndex() const;
	void setIndex(size_t index);
	const AttributeFilter& getAttributeFilter() const;
	void setAttributeFilter(const AttributeFilter& attributeFilter);
	const MyString& getAttributeExists() const;
	void setAttributeExists(const MyString& attributeExists);
};