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
