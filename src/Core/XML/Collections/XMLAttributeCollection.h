#pragma once
#include "../../../Utils/MyVector/MyVector.hpp"
#include "../Models/XMLAttribute.h"
#include "../../../Utils/MySharedPtr/MySharedPtr.hpp"

class XMLAttributeCollection : public MyVector<XMLAttribute>
{
public:
	XMLAttributeCollection() = default;
	explicit XMLAttributeCollection(size_t count);
	XMLAttribute* operator[](const MyString& attrName);
	const XMLAttribute* operator[](const MyString& attrName) const;
};