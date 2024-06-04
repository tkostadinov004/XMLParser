#include "XMLNode.h"

MyWeakPtr<XMLNode>& XMLNode::parent()
{
	return _parent;
}

const MyWeakPtr<XMLNode>& XMLNode::parent() const
{
	return _parent;
}

void XMLNode::setParent(const MyWeakPtr<XMLNode>& node)
{
	this->_parent = node;
}
