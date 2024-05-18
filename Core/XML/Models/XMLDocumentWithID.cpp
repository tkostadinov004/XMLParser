#include "XMLDocumentWithID.h"
#include "..\..\..\Utils\MyStack\MyStack.hpp"
#include "XMLTextNode.h"
GroupVector XMLDocumentWithID::idGroups;

static void convertNodeToWithID(XMLNode* node)
{
	if (XMLElementNode* elementNode = dynamic_cast<XMLElementNode*>(node))
	{
		XMLElementNodeWithID* newElementNode = dynamic_cast<XMLElementNodeWithID*>(node);
		for (int i = 0; i < elementNode->children().size(); i++)
		{
			XMLNode*& currentChild = elementNode->children()[i].get();
			if (auto textNode = dynamic_cast<const XMLTextNode*>(currentChild))
			{
				continue;
			}
			if (const XMLElementNode* childAsElementNode = dynamic_cast<const XMLElementNode*>(currentChild))
			{
				XMLElementNodeWithID* converted = new XMLElementNodeWithID(*childAsElementNode);
				delete currentChild;
				currentChild = converted;
			}

			convertNodeToWithID(currentChild);
			//XMLNode* child = new XMLElementNodeWithID(elementNode->getTagName(), "");// convertNodeToWithID(elementNode->children()[i].get());
			//newElementNode->addChild(child);
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

void XMLDocumentWithID::convertToXID(XMLNode* node)
{

}

void XMLDocumentWithID::resolveIdConflicts()
{
	resolveIdConflicts(_root);
}

XMLDocumentWithID::XMLDocumentWithID(const XMLDocument& xml)
{
	delete _root;
	_root = new XMLElementNodeWithID(*xml.root());
	convertNodeToWithID(_root);
	resolveIdConflicts();
}

std::ostream& operator<<(std::ostream& os, const XMLDocumentWithID& doc)
{
	return doc.root()->print(os);
}
