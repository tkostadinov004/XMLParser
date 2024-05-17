#pragma once
#include "XMLElementNode.h"
#include "..\..\..\Utils\GroupVector\GroupVector.h"
class XMLElementNodeWithID : public XMLElementNode
{
	static GroupVector idGroups;
public:
	XMLElementNodeWithID() = default;
	XMLElementNodeWithID(const XMLElementNode& node);
	XMLElementNodeWithID(const MyString& tagName, const MyString& id, XMLElementNodeWithID* parent = nullptr);
	const MyString& getId() const;
	void setid(const MyString& id);
};