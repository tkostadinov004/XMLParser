#include "XPathDescendantSelector.h"
#include "..\..\..\XML\Models\XMLElementNode.h"

XPathSelector* XPathDescendantSelector::clone() const
{
    return new XPathDescendantSelector(*this);
}

MyVector<const XMLNode*> XPathDescendantSelector::execute(const MyVector<const XMLNode*>& context, const XPathQueryComponent& component) const
{
	MyVector<const XMLNode*> result;
	for (size_t j = 0; j < context.size(); j++)
	{
		if (const XMLElementNode* current = dynamic_cast<const XMLElementNode*>(context[j]))
		{
			result.append_range(current->getDescendants()
				.filter([&component](const MySharedPtr<const XMLNode>& node)
					{
						const XMLElementNode* currentChild = dynamic_cast<const XMLElementNode*>(node.get());
						return currentChild && (component.getTag() == "*" || (currentChild->getTagName() == component.getTag() && (component.getNamespace().empty() || currentChild->getNamespace() && currentChild->getNamespace()->getName() == component.getNamespace())));
					})
				.convertTo<const XMLNode*>([](MySharedPtr<const XMLNode> ptr) {return ptr.get();}));
		}
	}
    return result;
}
