#pragma once
#include <ostream>
#include "../../../Utils/MyString/MyString.h"
#include "../../../Utils/MySharedPtr/MySharedPtr.hpp"

class XMLNode
{
	XMLNode* _parent;
public:
	virtual ~XMLNode() = default;
	explicit XMLNode(XMLNode* parent = nullptr);
	XMLNode* parent();
	const XMLNode* parent() const;
	void setParent(XMLNode* node);

	virtual MySharedPtr<XMLNode> clone() const = 0;
	virtual std::ostream& print(std::ostream& os, int indent = 0) const = 0;
};