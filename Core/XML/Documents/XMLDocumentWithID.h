#pragma once
#include "XMLDocument.h"
#include "../../../Utils/GroupVector/GroupVector.h"
#include "../Models/XMLElementNodeWithID.h"

class XMLDocumentWithID : public XMLDocument
{
	int generated = 0;
	GroupVector idGroups;
	void setIdToElement(XMLElementNodeWithID* element);
	void resolveIdConflicts(XMLElementNode* node);
	MySharedPtr<XMLElementNode> convertNodeToWithID(const MySharedPtr<XMLElementNode>& src, const MyWeakPtr<XMLElementNodeWithID>& parent);
public:
	void resolveIdConflicts();
	XMLDocumentWithID() = default;
	XMLDocumentWithID(const XMLDocument& xml);
};
std::ostream& operator<<(std::ostream& os, const XMLDocumentWithID& doc);