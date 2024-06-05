#include "XPathMixinSelector.h"

XPathMixinSelector::XPathMixinSelector(const MySharedPtr<XPathAxisSelector>& axisSelector, const MySharedPtr<XPathAttributeSelector>& attributeSelector) : _axisSelector(axisSelector), _attributeSelector(attributeSelector)
{
}

XPathSelector* XPathMixinSelector::clone() const
{
    return new XPathMixinSelector(*this);
}

MyVector<const XMLNode*> XPathMixinSelector::execute(const MyVector<const XMLNode*>& context, const XPathQueryComponent& component) const
{
    MyVector<const XMLNode*> axisResult = _axisSelector->execute(context, component);
    MyVector<const XMLNode*> attributeResult = _attributeSelector->execute(axisResult, component);
    return attributeResult;
}
