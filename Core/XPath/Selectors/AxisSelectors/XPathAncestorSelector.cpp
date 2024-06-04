#include "XPathAncestorSelector.h"
#include "..\..\..\XML\Models\XMLElementNode.h"

XPathSelector* XPathAncestorSelector::clone() const
{
	return new XPathAncestorSelector(*this);
}

MyVector<const XMLNode*> XPathAncestorSelector::execute(const MyVector<const XMLNode*>& context, const XPathQueryComponent& component) const
{
	MyVector<const XMLNode*> result;
	for (size_t j = 0; j < result.size(); j++)
	{
		if (const XMLElementNode* current = dynamic_cast<const XMLElementNode*>(context[j]))
		{
			result.append_range(current->getAncestors()
				.filter([&component](const MyWeakPtr< XMLElementNode>& node) {return node && (component.getTag() == "*" || (node->getTagName() == component.getTag() && (component.getNamespace().empty() || node->getNamespace() && node->getNamespace()->getName() == component.getNamespace())));})
				.convertTo<const XMLNode*>([](MyWeakPtr<XMLElementNode> ptr) {return ptr.get();}));
		}
	}
	return result;
}
