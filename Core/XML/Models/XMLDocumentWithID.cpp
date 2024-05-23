#include "XMLDocumentWithID.h"
#include "..\..\..\Utils\MyStack\MyStack.hpp"
#include "XMLTextNode.h"
GroupVector XMLDocumentWithID::idGroups;

static void convertNodeToWithID(MySharedPtr<XMLElementNode> node)
{
	for (int i = 0; i < node->children().size(); i++)
	{
		if (MySharedPtr<XMLElementNode> childAsElementNode = dynamic_cast<XMLElementNode*>(node->children()[i].get()))
		{
			MySharedPtr<XMLElementNodeWithID> converted = new XMLElementNodeWithID(*childAsElementNode);
			//delete currentChild;
			childAsElementNode = converted;
			convertNodeToWithID(converted);
		}
	}
}

void XMLDocumentWithID::setIdToElement(XMLElementNodeWithID* element)
{
	MyString resultId;
	if (XMLAttribute* idAttribute = element->_attributes["id"])
	{
		const MyString& id = idAttribute->getValue();
		resultId = id;
		idGroups.add(resultId);
		if (idGroups[id] > 1)
		{
			resultId += "_" + toString(idGroups[id]++);
		}
		idAttribute->setValue(resultId);
	}
	else
	{
		resultId = "auto_" + toString(++generated);
		idGroups.add(resultId);
		element->addAttribute(XMLAttribute("id", resultId));
	}

	element->setId(resultId);
}

void XMLDocumentWithID::resolveIdConflicts(XMLElementNode* root)
{
	for (size_t i = 0; i < root->children().size(); i++)
	{
		XMLElementNode* elementChild = dynamic_cast<XMLElementNode*>(root->children()[i].get());
		if (!elementChild) //text node
		{
			continue;
		}
		XMLElementNodeWithID* idChild = dynamic_cast<XMLElementNodeWithID*>(elementChild);
		if (idChild)
		{
			setIdToElement(idChild);
		}

		resolveIdConflicts(elementChild);
	}
}

void XMLDocumentWithID::resolveIdConflicts()
{
	resolveIdConflicts(_root.get());
}

XMLDocumentWithID::XMLDocumentWithID(const XMLDocument& xml)
{
	_root = new XMLElementNodeWithID(*xml.root());
	//convertNodeToWithID(_root);
	resolveIdConflicts();
}

std::ostream& operator<<(std::ostream& os, const XMLDocumentWithID& doc)
{
	return doc.root()->print(os);
}
