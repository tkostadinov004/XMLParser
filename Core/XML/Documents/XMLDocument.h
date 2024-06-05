#pragma once
#include <ostream>
#include "../Models/XMLElementNode.h"

class XMLDocument
{
protected:
	MySharedPtr<XMLElementNode> _root = nullptr;
public:
	XMLDocument(const MySharedPtr<XMLElementNode>& root = nullptr);
	virtual ~XMLDocument() = default;
	MySharedPtr<XMLElementNode>& root();
	const MySharedPtr<XMLElementNode>& root() const;
};
std::ostream& operator<<(std::ostream& os, const XMLDocument& doc);