#include "XPathQuery.h"
#include "..\..\XML\Models\XMLTextNode.h"

XPathQueryComponent XPathQuery::parseComponent(const MyString& component) const
{
	MyString componentCopy = component;

    XPathQueryComponent result;
	int axisSeparatorIndex = componentCopy.find("::");
	if (axisSeparatorIndex != -1)
	{
		result.setAxis(componentCopy.substr(0, axisSeparatorIndex));
		componentCopy = componentCopy.substr(axisSeparatorIndex + 2);
	}
	
	int predicateStartIndex = componentCopy.find("[");
	if (predicateStartIndex != -1)
	{
		result.setTag(componentCopy.substr(0, predicateStartIndex));
		componentCopy = componentCopy.substr(predicateStartIndex + 1);

		int comparativeSignIndex = componentCopy.find("=");
		if (comparativeSignIndex != -1)
		{
			AttributeFilter filter;
			filter._key = componentCopy.substr(1, comparativeSignIndex - 1);
			componentCopy = componentCopy.substr(comparativeSignIndex + 1);
			filter._value = componentCopy.substr(0, componentCopy.length() - 1);
			result.setAttributeFilter(filter);
		}
		else
		{
			if (componentCopy.ends_with("]"))
			{
				result.setAttributeExists(componentCopy.substr(1).takeWhile([](char c) {return c != ']';}));
			}
			else
			{
				result.setIndex(std::atoi(componentCopy.substr(1).takeWhile([](char c) {return c != ']';}).c_str()));
			}
		}
	}
	else
	{
		result.setTag(componentCopy);
	}
    return result;
}

MyVector<MyString> XPathQuery::evaluate(const MySharedPtr<XMLElementNode> root, const MyString& query)
{
	/*MyVector<const XMLNode*> result;
	result.push_back(root);

	MyVector<XPathQueryComponent> components = query.split('/').convertTo<XPathQueryComponent>([this](const MyString& str) {return this->parseComponent(str);});
	
	for (size_t i = 0; i < components.size(); i++)
	{
		const XPathQueryComponent& currentComponent = components[i];
		MyVector<const XMLNode*> nextElements;

		if (currentComponent.getAxis() == "child")
		{
			for (size_t j = 0; j < result.size(); j++)
			{
				if (const XMLElementNode* current = dynamic_cast<const XMLElementNode*>(result[j]))
				{
					MyVector<const XMLElementNode*> children =
						current->children()
						.convertTo<const XMLElementNode*>([](const MySharedPtr<XMLNode>& pw) {return dynamic_cast<const XMLElementNode*>(pw.get());})
						.filter([&currentComponent](const XMLElementNode* node) {return node && node->getTagName() == currentComponent.getTag();});
					if (currentComponent.getIndex() != -1 && currentComponent.getIndex() < children.size())
					{
						nextElements.push_back(children[currentComponent.getIndex()]);
					}
					else
					{
						nextElements.append_range(children.convertTo<const XMLNode*>([](const XMLElementNode* node) {return node;}));
					}
				}
			}
		}
		else if (currentComponent.getAxis() == "descendant")
		{
			for (size_t j = 0; j < result.size(); j++)
			{
				if (const XMLElementNode* current = dynamic_cast<const XMLElementNode*>(result[j]))
				{
					nextElements.append_range(current->getDescendants());
				}
			}
		}
		else if (currentComponent.getAxis() == "parent")
		{
			for (size_t j = 0; j < result.size(); j++)
			{
				if (const XMLNode* parent = result[j]->parent())
				{
					nextElements.push_back(parent);
				}
			}
		}
		else if (currentComponent.getAxis() == "ancestor")
		{
			for (size_t j = 0; j < result.size(); j++)
			{
				if (const XMLElementNode* current = dynamic_cast<const XMLElementNode*>(result[j]))
				{
					nextElements.append_range(current->getAncestors());
				}
			}
		}

		if (!currentComponent.getAttributeFilter()._key.empty())
		{
			nextElements = nextElements.filter([&currentComponent](const XMLNode* node)
				{
					if (const XMLElementNode* conv = dynamic_cast<const XMLElementNode*>(node))
					{
						const XMLAttribute* attribute = conv->attributes()[currentComponent.getAttributeFilter()._key];
						return attribute && attribute->getValue() == currentComponent.getAttributeFilter()._value;
					}
					return false;
				});
		}
		if (!currentComponent.getAttributeExists().empty())
		{
			nextElements = nextElements.filter([&currentComponent](const XMLNode* node)
				{
					if (const XMLElementNode* conv = dynamic_cast<const XMLElementNode*>(node))
					{
						return conv->attributes()[currentComponent.getAttributeExists()] != nullptr;
					}
					return false;
				});
		}
		result = nextElements;
	}
	
	return result.convertTo<MyString>([](const XMLNode* node)
		{
			if (const XMLTextNode* conv = dynamic_cast<const XMLTextNode*>(node))
			{
				return conv->textContent();
			}
			else
			{
				const XMLElementNode* conv1 = dynamic_cast<const XMLElementNode*>(node);
				return conv1->getTagName();
			}
		});*/
return MyVector<MyString>();
}
