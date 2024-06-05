#pragma once
#include "..\..\..\Utils\MyString\MyString.h"
#include "..\Models\XPathQueryComponent.h"
#include "..\..\XML\Models\XMLElementNode.h"

class XPathQuery
{
public:
	MyVector<const XMLNode*> evaluate(const MySharedPtr<XMLElementNode>& root, const MyString& queryString);
};