#include "XMLElementNodeWithID.h"
#include "XMLTextNode.h"

XMLElementNodeWithID::XMLElementNodeWithID(const MyString& tagName, const MyString& id, XMLElementNodeWithID* parent) : XMLElementNode(tagName, parent)
{
}

MySharedPtr<XMLNode> XMLElementNodeWithID::clone() const
{
	return new XMLElementNodeWithID(*this);
}

XMLElementNodeWithID::XMLElementNodeWithID(const XMLElementNode& node) : XMLElementNode(node)
{
	/*_children = _children.convertTo<MySharedPtr<XMLNode>>([](const MySharedPtr<XMLNode>& nodePtr)
		{
			XMLNode* result = nullptr;
			if (XMLElementNode* elPtr = dynamic_cast<XMLElementNode*>(nodePtr.get()))
			{
				result =  new XMLElementNodeWithID(*elPtr);
			}
			else if(XMLTextNode* textPtr = dynamic_cast<XMLTextNode*>(nodePtr.get()))
			{
				result = new XMLTextNode(*textPtr);
			}
			return result;
		});*/
}

const MyString& XMLElementNodeWithID::getId() const
{
	return _id;
}

void XMLElementNodeWithID::setId(const MyString& id)
{
	_id = id;
}
