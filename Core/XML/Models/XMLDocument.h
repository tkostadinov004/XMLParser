#pragma once
#include <ostream>
#include "XMLElementNode.h"

class XMLDocument
{
protected:
	XMLElementNode* _root;
	void copyFrom(const XMLDocument& other);
	void moveFrom(XMLDocument&& other) noexcept;
	void free();
public:
	XMLDocument();
	XMLDocument(const XMLDocument& other);
	XMLDocument(XMLDocument&& other) noexcept;
	XMLDocument& operator=(const XMLDocument& other);
	XMLDocument& operator=(XMLDocument&& other);
	virtual ~XMLDocument();
	XMLElementNode* root();
	const XMLElementNode* root() const;
};
std::ostream& operator<<(std::ostream& os, const XMLDocument& doc);