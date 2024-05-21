#pragma once
#include "..\..\..\Utils\MyString\MyString.h"
#include "..\Models\XPathQueryComponent.h"
#include "..\..\XML\Models\XMLElementNode.h"

class XPathQuery
{
	XPathQueryComponent parseComponent(const MyString& component) const;
public:
	MyVector<MyString> evaluate(const XMLElementNode* root, const MyString& query);
};