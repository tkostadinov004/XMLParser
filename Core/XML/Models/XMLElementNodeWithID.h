#pragma once
#include "XMLElementNode.h"
#include "..\..\..\Utils\GroupVector\GroupVector.h"
class XMLElementNodeWithID : public XMLElementNode
{
	MyString _id;
public:
	virtual MySharedPtr<XMLNode> clone() const override;
	const MyString& getId() const;
	void setId(const MyString& id);
	virtual MyString textContent() const override;
};