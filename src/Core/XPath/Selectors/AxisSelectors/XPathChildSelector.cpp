#include "XPathChildSelector.h"
#include "..\..\..\XML\Models\XMLElementNode.h"

XPathSelector* XPathChildSelector::clone() const
{
    return new XPathChildSelector(*this);
}

MyVector<const XMLNode*> XPathChildSelector::execute(const MyVector<const XMLNode*>& context, const XPathQueryComponent& component) const
{
	MyVector<const XMLNode*> result;
	for (size_t j = 0; j < context.size(); j++)
	{
		if (const XMLElementNode* current = dynamic_cast<const XMLElementNode*>(context[j]))
		{
			MyVector<const XMLElementNode*> children =
				current->children()
				.convertTo<const XMLElementNode*>([](const MySharedPtr<XMLNode>& pw) {return dynamic_cast<const XMLElementNode*>(pw.get());})
				.filter([&component](const XMLElementNode* node) {return node && node->getTagName() == component.getTag() && (component.getNamespace().empty() || node->getNamespace() && node->getNamespace()->getName() == component.getNamespace());});
			if (component.isIndexDefined())
			{
				if (component.getIndex() < children.size())
				{
					result.push_back(children[component.getIndex()]);
				}
			}
			else
			{
				result.append_range(children.convertTo<const XMLNode*>([](const XMLElementNode* node) {return node;}));
			}
		}
	}
    return result;
}
