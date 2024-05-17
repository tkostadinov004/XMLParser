#pragma once
#include <ostream>
#include "XMLElementNode.h"
#include "GroupVector.h"
class XMLDocument
{
protected:
	XMLElementNode _root;
public:
	virtual ~XMLDocument() = default;
	XMLDocument() = default;
	explicit XMLDocument(const XMLElementNode& root);
	MyVector<PointerWrapper<XMLNode>> traverse() const;
	XMLElementNode& root();
	const XMLElementNode& root() const;
};
std::ostream& operator<<(std::ostream& os, const XMLDocument& doc);