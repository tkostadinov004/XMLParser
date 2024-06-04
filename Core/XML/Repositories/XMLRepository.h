#pragma once
#include "Repository.hpp"
#include "../Models/XMLElementNode.h"
#include "../../../Utils/MyString/MyString.h"
#include "..\Models\XMLElementNodeWithID.h"
#include "..\Models\XMLDocumentWithID.h"
#include "../../../Utils/MyStack/MyStack.hpp"

class XMLRepository : public Repository<XMLElementNodeWithID>
{
	XMLDocumentWithID _xmlDocument;
	bool _isOpen = false;
public:
	void open(const MyString& path);
	void close();
	void saveAs(const MyString& path);

	void add(const XMLElementNodeWithID& item) override;
	bool remove(const XMLElementNodeWithID& item) override;
	bool remove(const MyString& id);
	MyString getContents() const;
	bool isOpen() const;
	//void selectAttribute(const MyString& nodeId, const MyString& attributeName) const;
	const MySharedPtr<XMLElementNodeWithID> find(std::function<bool(const MySharedPtr<XMLElementNodeWithID>)> pred) const;
	MySharedPtr<XMLElementNodeWithID> find(std::function<bool(MySharedPtr<XMLElementNodeWithID>)> pred);
	void resolveIdConflicts();
	MyVector<MyString> handleXPath(const MyString& query) const;
};