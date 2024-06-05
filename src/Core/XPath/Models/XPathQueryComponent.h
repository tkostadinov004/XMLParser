#pragma once
#include "..\..\..\Utils\MyString\MyString.h"
struct AttributeFilter
{
	MyString _key;
	bool _isQueryValue = false;
	MyString _value;
	MyString _namespace;
};
class XPathQueryComponent
{
	MyString _axis = "child";
	MyString _namespace;
	MyString _tag;
	bool _isIndexDefined = false;
	int _index = -1;
	AttributeFilter _attributeFilter;
public:
	const MyString& getAxis() const;
	void setAxis(const MyString& axis);
	const MyString& getTag() const;
	void setTag(const MyString& tag);
	const MyString& getNamespace() const;
	void setNamespace(const MyString& ns);
	bool isIndexDefined() const;
	void setIsIndexDefined(bool isIndexDefined);
	int getIndex() const;
	void setIndex(int index);
	const AttributeFilter& getAttributeFilter() const;
	void setAttributeFilter(const AttributeFilter& attributeFilter);
};