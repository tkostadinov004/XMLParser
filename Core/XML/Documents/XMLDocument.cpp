#include "XMLDocument.h"

XMLDocument::XMLDocument(const MySharedPtr<XMLElementNode>& root)
{
	_root = root;
}

MySharedPtr<XMLElementNode>& XMLDocument::root()
{
	return _root;
}

const MySharedPtr<XMLElementNode>& XMLDocument::root() const
{
	return _root;
}

std::ostream& operator<<(std::ostream& os, const XMLDocument& doc)
{
	return doc.root()->print(os);
}
