#include "XMLNode.h"

XMLNode::XMLNode(XMLNode* parent)
{
	setParent(parent);
}

XMLNode*& XMLNode::parent()
{
	return _parent;
}

const XMLNode* const& XMLNode::parent() const
{
	return _parent;
}

void XMLNode::setParent(XMLNode* node)
{
	this->_parent = node;
}
