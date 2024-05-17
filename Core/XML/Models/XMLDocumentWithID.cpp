#include "XMLDocumentWithID.h"
#include "..\..\..\Utils\MyStack\MyStack.hpp"

void XMLDocumentWithID::resolveIdConflicts(XMLElementNode& root, GroupVector& groups)
{
	//for (size_t i = 0; i < root.children().size(); i++)
	//{
	//	XMLElementNode* elementChild = dynamic_cast<XMLElementNode*>(root.children()[i].get());
	//	if (!elementChild) //text node
	//	{
	//		continue;
	//	}
	//	XMLAttribute* idAttribute = elementChild->_attributes["id"];
	//	if (idAttribute)
	//	{
	//		const MyString& id = idAttribute->getKey();
	//		if (groups[id] > 0)
	//		{
	//			int count = groups[id];
	//			groups[id]++;
	//			root._children[i]setId(id + "_" + std::to_string(count));
	//		}
	//	}


	//	if (groups[id] > 1)
	//	{
	//		int count = groups[id];
	//		groups[id]++;
	//		root->children()[i]->setId(id + "_" + std::to_string(count)); //!!!!!
	//	}
	//	else
	//	{
	//		groups.add(id);
	//	}

	//	resolveIdConflicts(root->children()[i], groups);
	//}
}

void XMLDocumentWithID::adaptFrom(XMLElementNodeWithID& previousParent, const XMLDocument& xml)
{
	_root = XMLElementNodeWithID(xml.root());
	/*MyStack<PointerWrapper<const XMLNode>> stack;

	stack.push(&xml.root());

	while (!stack.empty())
	{
		const XMLElementNode* temp = dynamic_cast<const XMLElementNode*>(stack.peek().get());
		if (!temp)
		{
			previousParent.addChild(*stack.peek());
			stack.pop();
		}
		else
		{
			stack.pop();
			for (int i = temp->children().size() - 1; i >= 0; i--)
			{
				previousParent = *previousParent._children[i];
				stack.push(temp->_children[i]);
			}
		}
	}*/
}

void XMLDocumentWithID::resolveIdConflicts()
{
	GroupVector groups;
	resolveIdConflicts(_root, groups);
}

XMLDocumentWithID::XMLDocumentWithID(const XMLDocument& xml)
{
	adaptFrom(_root, xml);
}

const XMLElementNodeWithID& XMLDocumentWithID::root() const
{
	return _root;
}

std::ostream& operator<<(std::ostream& os, const XMLDocumentWithID& doc)
{
	return doc.root().print(os);
}
