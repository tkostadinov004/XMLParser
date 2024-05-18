#include "XMLElementNodeWithID.h"

XMLElementNodeWithID::XMLElementNodeWithID(const MyString& tagName, const MyString& id, XMLElementNodeWithID* parent) : XMLElementNode(tagName, parent)
{
}

XMLElementNodeWithID::XMLElementNodeWithID(const XMLElementNode& node) : XMLElementNode(node)
{
	
}

const MyString& XMLElementNodeWithID::getId() const
{
	return _id;
}

void XMLElementNodeWithID::setId(const MyString& id)
{
	_id = id;
}
