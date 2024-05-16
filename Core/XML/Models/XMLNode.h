#pragma once
#include <ostream>
#include "../../../Utils/MyString/MyString.h"
class XMLNode
{
	XMLNode* _parent = nullptr;
	XMLNode* _rightSibling = nullptr;
public:
	explicit XMLNode(XMLNode* parent = nullptr);
	XMLNode* parent();
	const XMLNode* parent() const;
	XMLNode* rightSibling();
	const XMLNode* rightSibling() const;
	void setParent(XMLNode* node);

	virtual std::ostream& print(std::ostream& os, int indent = 0) const = 0;
};