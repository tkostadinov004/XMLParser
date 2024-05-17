#pragma once
#include <ostream>
#include "../../../Utils/MyString/MyString.h"
#include "../../../Utils/PointerWrapper/PointerWrapper.hpp"

class XMLNode
{
	XMLNode* _parent = nullptr;
public:
	virtual ~XMLNode() = default;
	explicit XMLNode(XMLNode* parent = nullptr);
	XMLNode*& parent();
	const XMLNode* const& parent() const;
	void setParent(XMLNode* node);

	virtual XMLNode* clone() const = 0;
	virtual std::ostream& print(std::ostream& os, int indent = 0) const = 0;
};