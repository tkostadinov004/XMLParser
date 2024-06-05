#pragma once
#include "../../../Utils/MyString/MyString.h"
#include "../../../Utils/MySharedPtr/MySharedPtr.hpp"
#include "../../../Utils/MyWeakPtr/MyWeakPtr.hpp"
#include "../Models/XMLNamespace.h"
class XMLElementNode;
class XMLAttribute
{
	MyString _key;
	MyString _value;
	MySharedPtr<XMLNamespace> _namespace = nullptr;
	MyWeakPtr<XMLElementNode> _owner;
public:
	XMLAttribute() = default;
	XMLAttribute(const MyString& key, const MyString& value);
	XMLAttribute(const MyString& key, const MyString& value, const MyString& namespaceName, const MyWeakPtr<XMLElementNode>& owner);
	virtual ~XMLAttribute() = default;

	const MyString& getKey() const;
	const MyString& getValue() const;

	void setKey(const MyString& key);
	void setValue(const MyString& value);

	const MySharedPtr<XMLNamespace>& getNamespace() const;
	void assignNamespace(const MyString& namespaceName);

	const MyWeakPtr<XMLElementNode>& getOwner() const;
	void setOwner(const MyWeakPtr<XMLElementNode>& node);

	MyString toString() const;
};