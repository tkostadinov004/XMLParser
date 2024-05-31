#include "XMLElementNodeWithID.h"
#include "XMLTextNode.h"

XMLElementNodeWithID::XMLElementNodeWithID(const MyString& tagName, const MyString& id) : XMLElementNode(tagName)
{
}

MySharedPtr<XMLNode> XMLElementNodeWithID::clone() const
{
	return new XMLElementNodeWithID(*this);
}

XMLElementNodeWithID::XMLElementNodeWithID(const XMLElementNode& node) : XMLElementNode(node)
{
	this->_definedNamespaces = _definedNamespaces.convertTo<MySharedPtr<XMLNamespace>>([](const MySharedPtr<XMLNamespace>& ptr) {return new XMLNamespace(*ptr);});
	if (this->_namespace)
	{
		this->_namespace = getDefinedNamespaceByName(this->_namespace->getName());
	}

	/*this->_children = _children.convertTo<MySharedPtr<XMLNode>>([](const MySharedPtr<XMLNode>& ptr)
		{
			MySharedPtr<XMLNode> result = nullptr;
			if (XMLElementNode* elPtr = dynamic_cast<XMLElementNode*>(ptr.get()))
			{
				result = new XMLElementNodeWithID(*elPtr);
			}
			else if (XMLTextNode* textPtr = dynamic_cast<XMLTextNode*>(ptr.get()))
			{
				result = new XMLTextNode(*textPtr);
			}
			return result;
		});*/
		//this->ns
		/*_children = _children.convertTo<MySharedPtr<XMLNode>>([](const MySharedPtr<XMLNode>& nodePtr)
			{
				MySharedPtr<XMLNode> result = nullptr;
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

MyString XMLElementNodeWithID::textContent() const
{
	return XMLElementNode::textContent();
}
