#pragma once
#include <ostream>
#include "XMLElementNode.h"

class XMLDocument
{
protected:
	XMLElementNode _root;
public:
	virtual ~XMLDocument() = default;
	XMLDocument() = default;
	explicit XMLDocument(const XMLElementNode& root);
	XMLElementNode& root();
	const XMLElementNode& root() const;
};
std::ostream& operator<<(std::ostream& os, const XMLDocument& doc);