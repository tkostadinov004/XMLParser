#include "XMLNode.h"

XMLNode::XMLNode(XMLNode* parent)
{
	setParent(parent);
}

XMLNode* XMLNode::parent()
{
	return _parent;
}

XMLNode* XMLNode::rightSibling()
{
	return _rightSibling;
}

void XMLNode::setRightSibling(XMLNode* node)
{
	_rightSibling = node;
}

const XMLNode* XMLNode::rightSibling() const
{
	return _rightSibling;
}

const XMLNode* XMLNode::parent() const
{
	return _parent;
}

void XMLNode::setParent(XMLNode* node)
{
	this->_parent = node;
}
