#pragma once
#include "XMLElementNode.h"
#include "..\..\..\Utils\GroupVector\GroupVector.h"
class XMLElementNodeWithID : public XMLElementNode
{
	MyString _id;
public:
	XMLElementNodeWithID() = default;
	explicit XMLElementNodeWithID(const MyString& tagName);
	virtual MySharedPtr<XMLNode> clone() const override;
	const MyString& getId() const;
	void setId(const MyString& id);
	virtual MyString textContent() const override;
};