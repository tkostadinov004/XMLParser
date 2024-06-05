#pragma once
#include "XMLDocument.h"
#include "../../../Utils/GroupVector/GroupVector.h"
#include "../Models/XMLElementNodeWithID.h"

class XMLDocumentWithID : public XMLDocument
{
	int _generated = 0;
	GroupVector _idGroups;
	void setIdToElement(XMLElementNodeWithID* element);
	void resolveIdConflicts(XMLElementNode* node);
	MySharedPtr<XMLElementNode> convertNodeToWithID(MySharedPtr<XMLElementNode> src, MyWeakPtr<XMLElementNodeWithID> parent);
public:
	void resolveIdConflicts();
	XMLDocumentWithID() = default;
	XMLDocumentWithID(const XMLDocument& xml);
	void clearIdGroups();
};
std::ostream& operator<<(std::ostream& os, const XMLDocumentWithID& doc);