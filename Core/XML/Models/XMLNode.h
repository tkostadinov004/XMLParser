#pragma once
#include "../../../Utils/MyVector/MyVector.hpp"
#include "../../../Utils/MyString/MyString.h"
#include "XMLAttribute.h"
#include "XMLNamespace.h"
#include "XMLElement.h"

class XMLNode : public XMLElement
{
	const XMLNamespace* _namespace = nullptr;
	MyString _tagName;
	XMLNode* _parent = nullptr;
	MyVector<XMLAttribute> _attributes;
	MyVector<XMLElement*> _children;
	MyVector<XMLNamespace> _definedNamespaces;

	std::ostream& print(std::ostream& os) const override;
public:
	XMLNode() = default;
	explicit XMLNode(const MyString& tagName, XMLNode* parent = nullptr);

	const XMLNamespace* getNamespace() const;
	const MyString& getTagName() const;
	XMLNode* parent();
	const MyVector<XMLAttribute>& attributes() const;
	const MyVector<XMLElement*>& children() const;
	const MyVector<XMLNamespace>& definedNamespaces() const;
	bool canHaveNamespace(const MyString& nsName) const;

	void setTagName(const MyString& tagName);
	void setParent(XMLNode* parent);
	void setNamespace(const XMLNamespace& xmlNamespace);
	void addAttribute(const XMLAttribute& attribute);
	void addAttributes(const MyVector<XMLAttribute>& attributes);
	void addChild(XMLElement* child);
	void defineNamespace(XMLNamespace& xmlNamespace);
};