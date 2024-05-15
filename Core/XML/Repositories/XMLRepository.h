#pragma once
#include "Repository.hpp"
#include "../Models/XMLNode.h"
#include "../Models/XMLDocument.h"
#include "../../../Utils/MyString/MyString.h"

class XMLRepository : public Repository<XMLNode>
{
	XMLDocument _xmlDocument;
public:
	void open(const MyString& path);
	void close();
	void save();
	void saveas(const MyString& path);

	void add(const XMLNode& item) override;
	bool remove(const XMLNode& item) override;
	bool remove(const MyString& id);
	const XMLNode*& find(bool(*pred)(XMLNode)) const override;
};