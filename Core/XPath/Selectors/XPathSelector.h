#pragma once
#include "..\Models\XPathQueryComponent.h"
#include "..\..\XML\Models\XMLNode.h"
class XPathSelector
{
public:
	virtual ~XPathSelector() = default;
	virtual XPathSelector* clone() const = 0;
	virtual MyVector<const XMLNode*> execute(const MyVector<const XMLNode*>& context, const XPathQueryComponent& component) const = 0;
};