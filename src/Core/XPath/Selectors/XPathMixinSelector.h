#pragma once
#include "AxisSelectors\XPathAxisSelector.h"
#include "AttributeSelectors\XPathAttributeSelector.h"
class XPathMixinSelector : public XPathSelector
{
	MySharedPtr<XPathAxisSelector> _axisSelector;
	MySharedPtr<XPathAttributeSelector> _attributeSelector;
public:
	explicit XPathMixinSelector(const MySharedPtr<XPathAxisSelector>& axisSelector, const MySharedPtr<XPathAttributeSelector>& attributeSelector);
	virtual XPathSelector* clone() const override;
	virtual MyVector<const XMLNode*> execute(const MyVector<const XMLNode*>& context, const XPathQueryComponent& component) const override;
};