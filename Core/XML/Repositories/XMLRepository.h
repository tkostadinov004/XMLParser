#pragma once
#include "Repository.hpp"
#include "../Models/XMLElementNode.h"
#include "../../../Utils/MyString/MyString.h"
#include "..\Models\XMLElementNodeWithID.h"
#include "..\Models\XMLDocumentWithID.h"

class XMLRepository : public Repository<XMLElementNodeWithID>
{
	XMLDocumentWithID _xmlDocument;
public:
	void open(const MyString& path);
	void close();
	void saveAs(const MyString& path);

	void add(const XMLElementNodeWithID& item) override;
	bool remove(const XMLElementNodeWithID& item) override;
	bool remove(const MyString& id);
	const XMLElementNodeWithID*& find(bool(*pred)(XMLElementNodeWithID)) const override;
};