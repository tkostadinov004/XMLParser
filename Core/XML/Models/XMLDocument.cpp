#include "XMLDocument.h"
#include "..\..\..\Utils\MyStack\MyStack.hpp"

XMLDocument::XMLDocument(XMLNode* root)
{
	this->_root = root;
}

MyVector<const XMLElement*> XMLDocument::traverse() const
{
	MyStack<const XMLElement*> stack;
	MyVector<const XMLElement*> preorder;

	stack.push(_root);

	while (!stack.empty()) 
	{
		const XMLNode* temp = dynamic_cast<const XMLNode*>(stack.peek());
		if (!temp)
		{
			preorder.push_back(stack.peek());
		}
		else
		{
			preorder.push_back(temp);
		}
		stack.pop();
		for (int i = temp->children().size() - 1; i >= 0; i--) 
		{
			stack.push(temp->children()[i]);
		}
	}
	return preorder;
}


XMLNode* XMLDocument::root() const
{
	return _root;
}

std::ostream& operator<<(std::ostream& os, const XMLDocument& doc)
{
	MyVector<const XMLElement*> traversal = doc.traverse();
	for (size_t i = 0; i < traversal.size(); i++)
	{
		os << *traversal[i];
	}
	return os;
}
