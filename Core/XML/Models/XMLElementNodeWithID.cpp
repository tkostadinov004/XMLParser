#include "XMLElementNodeWithID.h"
#include "XMLTextNode.h"


MySharedPtr<XMLNode> XMLElementNodeWithID::clone() const
{
	return new XMLElementNodeWithID(*this);
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
