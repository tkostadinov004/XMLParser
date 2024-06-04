#pragma once
#include "../../../Utils/MyVector/MyVector.hpp"
#include "../../../Utils/MyString/MyString.h"
#include "XMLAttribute.h"
#include "XMLNamespace.h"
#include "XMLNode.h"
#include "..\..\..\Utils\MySharedPtr\MySharedPtr.hpp"
#include "XMLAttributeCollection.h"

class XMLElementNode : public XMLNode
{
protected:
	MySharedPtr<XMLNamespace> _namespace;
	MyString _tagName;
	XMLAttributeCollection _attributes;
	MyVector<MySharedPtr<XMLNode>> _children;
	MyVector<MySharedPtr<XMLNamespace>> _definedNamespaces;
public:
	XMLElementNode() = default;
	explicit XMLElementNode(const MyString& tagName);
	virtual MySharedPtr<XMLNode> clone() const override;

	const MySharedPtr<XMLNamespace>& getNamespace() const;
	const MyString& getTagName() const;
	const XMLAttributeCollection& attributes() const;
	const MyVector<MySharedPtr<XMLNode>>& children() const;
	MyVector<MySharedPtr<XMLNode>>& children();
	MyVector<MySharedPtr<const XMLNode>> getDescendants() const;
	MyVector<MyWeakPtr<XMLElementNode>> getAncestors() const;
	const MyVector<MySharedPtr<XMLNamespace>>& definedNamespaces() const;
	const MySharedPtr<XMLNamespace>& getDefinedNamespaceByName(const MyString& nsName) const;

	void setTagName(const MyString& tagName);
	void assignNamespace(const MyString& namespaceName);
	void addAttribute(const XMLAttribute& attribute);
	void addAttributes(const MyVector<XMLAttribute>& attributes);
	void addNamespaces(const MyVector<XMLNamespace>& namespaces);
	void changeAttribute(const MyString& attributeName, const MyString& newValue);
	bool deleteAttribute(const MyString& attributeName);
	bool hasTextChild(const MyString& content) const;
	void addChild(const MySharedPtr<XMLNode>& child);
	void addChild(const XMLNode& child);

	std::ostream& print(std::ostream& os, int indent = 0) const override;
	virtual MyString textContent() const override;

	friend class XMLDocument;
	friend class XMLDocumentWithID;
};