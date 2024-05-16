#include "XMLTextNode.h"
#include <iomanip>

XMLTextNode::XMLTextNode(const MyString& textContent, XMLNode* parent) : XMLNode(parent)
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
	if (rightSibling())
	{
		os  << std::setfill(' ') << std::setw(indent * 3) << "";
	}
	return os << _textContent;
}