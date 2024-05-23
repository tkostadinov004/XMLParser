#include "XMLNode.h"

//XMLNode::XMLNode(MyWeakPtr<XMLNode> parent)
//{
//	setParent(parent);
//}

MyWeakPtr<XMLNode> XMLNode::parent()
{
	return _parent;
}

const MyWeakPtr<XMLNode> XMLNode::parent() const
{
	return _parent;
}

void XMLNode::setParent(MyWeakPtr<XMLNode> node)
{
	this->_parent = node;
}
