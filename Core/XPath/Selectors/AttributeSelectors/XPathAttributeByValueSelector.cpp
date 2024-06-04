#include "XPathAttributeByValueSelector.h"
#include "..\..\..\XML\Models\XMLElementNode.h"

XPathSelector* XPathAttributeByValueSelector::clone() const
{
    return new XPathAttributeByValueSelector(*this);
}

MyVector<const XMLNode*> XPathAttributeByValueSelector::execute(const MyVector<const XMLNode*>& context, const XPathQueryComponent& component) const
{
	MyVector<const XMLNode*> result = context.filter([&component](const XMLNode* node)
		{
			if (const XMLElementNode* conv = dynamic_cast<const XMLElementNode*>(node))
			{
				const XMLAttribute* attribute = conv->attributes()[component.getAttributeFilter()._key];
				return attribute && attribute->getValue() == component.getAttributeFilter()._value && (component.getAttributeFilter()._namespace.empty() || (attribute->getNamespace() && component.getAttributeFilter()._namespace == attribute->getNamespace()->getName()));
			}
			return false;
		});
    return result;
}
