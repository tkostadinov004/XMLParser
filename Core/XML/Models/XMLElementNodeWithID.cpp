#include "XMLElementNodeWithID.h"

XMLElementNodeWithID::XMLElementNodeWithID(const MyString& tagName, const MyString& id, XMLElementNodeWithID* parent) : XMLElementNode(tagName, parent)
{
}

XMLNode* XMLElementNodeWithID::clone() const
{
	return new XMLElementNodeWithID(*this);
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
