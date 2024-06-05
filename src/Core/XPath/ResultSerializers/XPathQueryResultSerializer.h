#pragma once
#include "..\..\..\Utils\MyString\MyString.h"
#include "..\..\XML\Models\XMLElementNode.h"
class XPathQueryResultSerializer
{
public:
	MyString serializeResult(const MyVector<const XMLNode*>& result) const;
};