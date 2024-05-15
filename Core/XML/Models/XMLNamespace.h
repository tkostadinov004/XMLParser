#pragma once
#include "../../../Utils/MyString/MyString.h"
#include "XMLAttribute.h"
class XMLNamespace : public XMLAttribute
{
public:
	XMLNamespace() = default;
	XMLNamespace(const MyString& key, const MyString& value);
};