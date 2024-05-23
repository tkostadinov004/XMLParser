#pragma once
#include <ostream>
#include "../../../Utils/MyString/MyString.h"
#include "../../../Utils/MySharedPtr/MySharedPtr.hpp"
#include "..\..\..\Utils\MyWeakPtr\MyWeakPtr.hpp"

class XMLNode
{
	MyWeakPtr<XMLNode> _parent;
public:
	virtual ~XMLNode() = default;
	XMLNode() = default;
	MyWeakPtr<XMLNode> parent();
	const MyWeakPtr<XMLNode> parent() const;
	void setParent(MyWeakPtr<XMLNode> node);

	virtual MySharedPtr<XMLNode> clone() const = 0;
	virtual std::ostream& print(std::ostream& os, int indent = 0) const = 0;
	virtual MyString textContent() const = 0;
};