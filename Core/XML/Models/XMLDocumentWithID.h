#pragma once
#include "XMLDocument.h"
#include "../../../Utils/GroupVector/GroupVector.h"
#include "../Models/XMLElementNodeWithID.h"

class XMLDocumentWithID
{
	XMLElementNodeWithID _root;
	void resolveIdConflicts(XMLElementNode& node, GroupVector& groups);
	void adaptFrom(XMLElementNodeWithID& previousParent, const XMLDocument& xml);
public:
	void resolveIdConflicts();
	XMLDocumentWithID() = default;
	XMLDocumentWithID(const XMLDocument& xml);
	const XMLElementNodeWithID& root() const;
};
std::ostream& operator<<(std::ostream& os, const XMLDocumentWithID& doc);