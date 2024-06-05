#pragma once
#include "XPathAttributeSelector.h"
#include "../../../XML/Models/XMLNode.h"
class XPathAttributeByValueSelector : public XPathAttributeSelector
{
public:
	virtual XPathSelector* clone() const override;
	virtual MyVector<const XMLNode*> execute(const MyVector<const XMLNode*>& context, const XPathQueryComponent& component) const override;
};