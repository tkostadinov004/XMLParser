#pragma once
#include "XMLDocument.h"
#include "../../../Utils/GroupVector/GroupVector.h"
#include "../Models/XMLElementNodeWithID.h"
#include "XMLElementNodeWithID.h"

class XMLDocumentWithID : public XMLDocument
{
	int generated = 0;
	static GroupVector idGroups;
	void setIdToElement(XMLElementNodeWithID* element);
	void resolveIdConflicts(XMLElementNode* node);
	MySharedPtr<XMLElementNode> convertNodeToWithID(MySharedPtr<XMLElementNode> src, MyWeakPtr<XMLElementNode> parent);
public:
	void resolveIdConflicts();
	XMLDocumentWithID() = default;
	XMLDocumentWithID(const XMLDocument& xml);
};
std::ostream& operator<<(std::ostream& os, const XMLDocumentWithID& doc);