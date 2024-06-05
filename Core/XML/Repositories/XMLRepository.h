#pragma once
#include "../Models/XMLElementNode.h"
#include "../../../Utils/MyString/MyString.h"
#include "..\Models\XMLElementNodeWithID.h"
#include "..\Documents\XMLDocumentWithID.h"
#include "../../../Utils/MyStack/MyStack.hpp"

class XMLRepository
{
	XMLDocumentWithID _xmlDocument;
	bool _isOpen = false;
public:
	void open(const MyString& path);
	void close();
	void saveAs(const MyString& path);

	MyString getContents() const;
	bool isOpen() const;

	const MySharedPtr<XMLElementNodeWithID>& find(std::function<bool(const MySharedPtr<XMLElementNodeWithID>&)> pred) const;
	MySharedPtr<XMLElementNodeWithID> find(std::function<bool(MySharedPtr<XMLElementNodeWithID>)> pred);
	void resolveIdConflicts();
	MyVector<const XMLNode*> handleXPath(const MyString& query) const;
};