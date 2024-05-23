#pragma once
#include "../../../Utils/MyString/MyString.h"
#include "XMLNode.h"

class XMLTextNode : public XMLNode
{
	MyString _textContent;
public:
	virtual MySharedPtr<XMLNode> clone() const override;
	XMLTextNode(const MyString& textContent);
	const MyString& textContent() const;
	void setTextContent(const MyString& textContent);
	std::ostream& print(std::ostream& os, int indent = 0) const override;
};