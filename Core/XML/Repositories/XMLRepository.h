#pragma once
#include "Repository.hpp"
#include "../Models/XMLElementNode.h"
#include "../Models/XMLDocument.h"
#include "../../../Utils/MyString/MyString.h"

class XMLRepository : public Repository<XMLElementNode>
{
	XMLDocument _xmlDocument;
public:
	void open(const MyString& path);
	void close();
	void save();
	void saveas(const MyString& path);

	void add(const XMLElementNode& item) override;
	bool remove(const XMLElementNode& item) override;
	bool remove(const MyString& id);
	const XMLElementNode*& find(bool(*pred)(XMLElementNode)) const override;
};