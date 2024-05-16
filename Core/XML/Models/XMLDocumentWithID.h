#pragma once
#include "XMLDocument.h"

class XMLDocumentWithID : public XMLDocument
{
	void resolveIdConflicts(XMLElementNode* node, GroupVector& groups);
public:
	void resolveIdConflicts();
};