#include "XMLDocument.h"
#include "..\..\..\Utils\MyStack\MyStack.hpp"

XMLDocument::XMLDocument(const XMLElementNode& root)
{
	this->_root = root;
}

MyVector< PointerWrapper<XMLNode>> XMLDocument::traverse() const
{
	MyStack<PointerWrapper<XMLNode>> stack;
	MyVector<PointerWrapper<XMLNode>> preorder;

	/*stack.push(_root);

	while (!stack.empty()) 
	{
		const XMLElementNode* temp = dynamic_cast<const XMLElementNode*>(stack.peek().get());
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
	}*/
	return preorder;
}


XMLElementNode& XMLDocument::root()
{
	return _root;
}
const XMLElementNode& XMLDocument::root() const
{
	return _root;
}

std::ostream& operator<<(std::ostream& os, const XMLDocument& doc)
{
	return doc.root().print(std::cout);
}
