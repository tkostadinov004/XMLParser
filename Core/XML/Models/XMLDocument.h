#pragma once
#include <ostream>
#include "XMLNode.h"
#include "GroupVector.h"
class XMLDocument
{
protected:
	XMLNode* _root = nullptr;
public:
	explicit XMLDocument(XMLNode* root = nullptr);
	MyVector<const XMLElement*> traverse() const;
	XMLNode* root() const;
};
std::ostream& operator<<(std::ostream& os, const XMLDocument& doc);