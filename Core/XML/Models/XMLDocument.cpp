#include "XMLDocument.h"

void XMLDocument::copyFrom(const XMLDocument& other)
{
	_root = dynamic_cast<XMLElementNode*>(other._root->clone());
}

void XMLDocument::moveFrom(XMLDocument&& other) noexcept
{
	_root = other._root;
	other._root = nullptr;
}

void XMLDocument::free()
{
	delete _root;
}

XMLDocument::XMLDocument()
{
	_root = new XMLElementNode();
}

XMLDocument::XMLDocument(const XMLDocument& other)
{
	copyFrom(other);
}

XMLDocument::XMLDocument(XMLDocument&& other) noexcept
{
	moveFrom(std::move(other));
}

XMLDocument& XMLDocument::operator=(const XMLDocument& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

XMLDocument& XMLDocument::operator=(XMLDocument&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

XMLDocument::~XMLDocument()
{
	free();
}

XMLElementNode* XMLDocument::root()
{
	return _root;
}

const XMLElementNode* XMLDocument::root() const
{
	return _root;
}

std::ostream& operator<<(std::ostream& os, const XMLDocument& doc)
{
	return doc.root()->print(os);
}
