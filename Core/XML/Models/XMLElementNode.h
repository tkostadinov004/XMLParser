#pragma once
#include "../../../Utils/MyVector/MyVector.hpp"
#include "../../../Utils/MyString/MyString.h"
#include "XMLAttribute.h"
#include "XMLNamespace.h"
#include "XMLNode.h"

class XMLElementNode : public XMLNode
{
	const XMLNamespace* _namespace = nullptr;
	MyString _tagName;
	MyVector<XMLAttribute> _attributes;
	MyVector<XMLNode*> _children;
	MyVector<XMLNamespace> _definedNamespaces;
public:
	XMLElementNode() = default;
	explicit XMLElementNode(const MyString& tagName, XMLElementNode* parent = nullptr);

	const XMLNamespace* getNamespace() const;
	const MyString& getTagName() const;
	const MyVector<XMLAttribute>& attributes() const;
	const MyVector<XMLNode*>& children() const;
	const MyVector<XMLNamespace>& definedNamespaces() const;
	const XMLNamespace* getDefinedNamespaceByName(const MyString& nsName) const;

	void setTagName(const MyString& tagName);
	void assignNamespace(const XMLNamespace& ns);
	void addAttribute(const XMLAttribute& attribute);
	void addAttributes(const MyVector<XMLAttribute>& attributes);
	void addChild(XMLNode* child);
	void defineNamespace(XMLNamespace& xmlNamespace);

	std::ostream& print(std::ostream& os, int indent = 0) const override;
};