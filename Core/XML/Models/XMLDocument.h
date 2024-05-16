#pragma once
#include <ostream>
#include "XMLElementNode.h"
#include "GroupVector.h"
class XMLDocument
{
protected:
	XMLElementNode* _root = nullptr;
public:
	explicit XMLDocument(XMLElementNode* root = nullptr);
	MyVector<const XMLNode*> traverse() const;
	XMLElementNode* root() const;
};
std::ostream& operator<<(std::ostream& os, const XMLDocument& doc);