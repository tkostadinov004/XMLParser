#pragma once
#include "../../../Utils/MyVector/MyVector.hpp"
#include "../../../Utils/MyString/MyString.h"
#include "XMLAttribute.h"
#include "XMLNamespace.h"
#include "XMLNode.h"
#include "..\..\..\Utils\PointerWrapper\PointerWrapper.hpp"
#include "XMLAttributeCollection.h"

class XMLElementNode : public XMLNode
{
protected:
	const XMLNamespace* _namespace = nullptr;
	MyString _tagName;
	XMLAttributeCollection _attributes;
	MyVector<PointerWrapper<XMLNode>> _children;
	MyVector<XMLNamespace> _definedNamespaces;
public:
	XMLElementNode() = default;
	explicit XMLElementNode(const MyString& tagName, XMLElementNode* parent = nullptr);
	virtual XMLNode* clone() const override;

	const XMLNamespace* getNamespace() const;
	const MyString& getTagName() const;
	const XMLAttributeCollection& attributes() const;
	const MyVector<PointerWrapper<XMLNode>>& children() const;
	MyVector<PointerWrapper<XMLNode>>& children();
	const MyVector<XMLNamespace>& definedNamespaces() const;
	const XMLNamespace* getDefinedNamespaceByName(const MyString& nsName) const;

	void setTagName(const MyString& tagName);
	void assignNamespace(const XMLNamespace& ns);
	void addAttribute(const XMLAttribute& attribute);
	void addAttributes(const MyVector<XMLAttribute>& attributes);
	void addChild(XMLNode* child);
	void addChild(const XMLNode& child);
	void defineNamespace(XMLNamespace& xmlNamespace);

	std::ostream& print(std::ostream& os, int indent = 0) const override;

	friend class XMLDocument;
	friend class XMLDocumentWithID;
};