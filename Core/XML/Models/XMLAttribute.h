#pragma once
#include "../../../Utils/MyString/MyString.h"
#include "../../../Utils/MySharedPtr/MySharedPtr.hpp"
#include "../../../Utils/MyWeakPtr/MyWeakPtr.hpp"
#include "../Models/XMLNamespace.h"
#include "XMLNode.h"
class XMLAttribute
{
	MyString _key;
	MyString _value;
	MySharedPtr<XMLNamespace> _namespace = nullptr;
	MyWeakPtr<XMLNode> _owner;
public:
	XMLAttribute() = default;
	XMLAttribute(const MyString& key, const MyString& value);
	XMLAttribute(const MyString& key, const MyString& value, const MyString& namespaceName, MyWeakPtr<XMLNode> owner);
	virtual ~XMLAttribute() = default;

	const MyString& getKey() const;
	const MyString& getValue() const;

	void setKey(const MyString& key);
	void setValue(const MyString& value);

	const MySharedPtr<XMLNamespace>& getNamespace() const;
	void assignNamespace(const MyString& namespaceName);

	const MyWeakPtr<XMLNode>& getOwner() const;
	void setOwner(const MyWeakPtr<XMLNode>& node);

	MyString toString() const;
};