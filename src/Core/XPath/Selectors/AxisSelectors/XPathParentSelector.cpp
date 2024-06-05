#include "XPathParentSelector.h"
#include "..\..\..\XML\Models\XMLElementNode.h"

XPathSelector* XPathParentSelector::clone() const
{
    return new XPathParentSelector(*this);
}

MyVector<const XMLNode*> XPathParentSelector::execute(const MyVector<const XMLNode*>& context, const XPathQueryComponent& component) const
{
	MyVector<const XMLNode*> result;
	for (size_t j = 0; j < context.size(); j++)
	{
		if (const XMLElementNode* parent = dynamic_cast<const XMLElementNode*>(context[j]->parent().get()))
		{
			if (component.getTag() == "*" || (parent->getTagName() == component.getTag() && (component.getNamespace().empty() || parent->getNamespace() && parent->getNamespace()->getName() == component.getNamespace())))
			{
				result.push_back(parent);
			}
		}
	}
    return result;
}
