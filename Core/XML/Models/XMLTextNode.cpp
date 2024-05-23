#include "XMLTextNode.h"
#include <iomanip>

MySharedPtr<XMLNode> XMLTextNode::clone() const
{
	return new XMLTextNode(*this);
}

XMLTextNode::XMLTextNode(const MyString& textContent)
{
	setTextContent(textContent);
}

const MyString& XMLTextNode::textContent() const
{
	return _textContent;
}

void XMLTextNode::setTextContent(const MyString& textContent)
{
	_textContent = textContent;
}

std::ostream& XMLTextNode::print(std::ostream& os, int indent) const
{
	/*if (parent()->)
	{

	}*/
	return os << std::setfill(' ') << std::setw(indent * 3) << "" << _textContent;
}