#include "XPathAttributeByExistenceSelector.h"
#include "..\..\..\XML\Models\XMLElementNode.h"

XPathSelector* XPathAttributeByExistenceSelector::clone() const
{
    return new XPathAttributeByExistenceSelector(*this);
}

MyVector<const XMLNode*> XPathAttributeByExistenceSelector::execute(const MyVector<const XMLNode*>& context, const XPathQueryComponent& component) const
{
	MyVector<const XMLNode*> result = context.filter([&component](const XMLNode* node)
		{
			if (const XMLElementNode* conv = dynamic_cast<const XMLElementNode*>(node))
			{
				const XMLAttribute* attribute = conv->attributes()[component.getAttributeFilter()._key];
				return attribute && (component.getAttributeFilter()._namespace.empty() || (attribute->getNamespace() && component.getAttributeFilter()._namespace == attribute->getNamespace()->getName()));
			}
			return false;
		});
	return result;
}
