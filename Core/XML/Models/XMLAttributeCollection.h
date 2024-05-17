#pragma once
#include "../../../Utils/MyVector/MyVector.hpp"
#include "XMLAttribute.h"

class XMLAttributeCollection : public MyVector<XMLAttribute>
{
public:
	XMLAttributeCollection() = default;
	explicit XMLAttributeCollection(size_t count);
	XMLAttribute* operator[](const MyString& attrName);
	const XMLAttribute* operator[](const MyString& attrName) const;
};