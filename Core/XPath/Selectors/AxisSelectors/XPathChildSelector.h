#pragma once
#include "XPathAxisSelector.h"
#include "..\..\..\XML\Models\XMLNode.h"
class XPathChildSelector : public XPathAxisSelector
{
public:
	virtual XPathSelector* clone() const override;
	virtual MyVector<const XMLNode*> execute(const MyVector<const XMLNode*>& context, const XPathQueryComponent& component) const override;
};