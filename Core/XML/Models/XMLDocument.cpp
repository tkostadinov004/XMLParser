#include "XMLDocument.h"

XMLDocument::XMLDocument(const XMLElementNode& root)
{
	this->_root = root;
}


XMLElementNode& XMLDocument::root()
{
	return _root;
}

const XMLElementNode& XMLDocument::root() const
{
	return _root;
}

std::ostream& operator<<(std::ostream& os, const XMLDocument& doc)
{
	return doc.root().print(os);
}
