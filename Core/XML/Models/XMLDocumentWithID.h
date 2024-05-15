#pragma once
#include "XMLDocument.h"

class XMLDocumentWithID : public XMLDocument
{
	void resolveIdConflicts(XMLNode* node, GroupVector& groups);
public:
	void resolveIdConflicts();
};