#include "XMLDocument.h"
#include "..\..\..\Utils\MyStack\MyStack.hpp"

XMLDocument::XMLDocument(XMLElementNode* root)
{
	this->_root = root;
}

MyVector<const XMLNode*> XMLDocument::traverse() const
{
	MyStack<const XMLNode*> stack;
	MyVector<const XMLNode*> preorder;

	stack.push(_root);

	while (!stack.empty()) 
	{
		const XMLElementNode* temp = dynamic_cast<const XMLElementNode*>(stack.peek());
		if (!temp)
		{
			preorder.push_back(stack.peek());
			stack.pop();
		}
		else
		{
			preorder.push_back(temp);
			stack.pop();
			for (int i = temp->children().size() - 1; i >= 0; i--)
			{
				stack.push(temp->children()[i]);
			}
		}	
	}
	return preorder;
}


XMLElementNode* XMLDocument::root() const
{
	return _root;
}

std::ostream& operator<<(std::ostream& os, const XMLDocument& doc)
{
	MyVector<const XMLNode*> traversal = doc.traverse();
	for (size_t i = 0; i < traversal.size(); i++)
	{
		traversal[i]->print(std::cout);
	}
	return std::cout;
}
