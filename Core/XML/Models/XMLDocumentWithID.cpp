#include "XMLDocumentWithID.h"
#include "..\..\..\Utils\MyStack\MyStack.hpp"
#include "XMLTextNode.h"
GroupVector XMLDocumentWithID::idGroups;

bool isRootSet = false;
static void convertNodeToWithID(MySharedPtr<XMLNode> node)
{
	if (!node)
	{
		return;
	}
	if (auto elementNode = dynamic_cast<XMLElementNode*>(node.get())) 
	{
		auto newNode = MySharedPtr<XMLElementNodeWithID>(new XMLElementNodeWithID(*elementNode));
		node = newNode;
	}

	if (auto elementNode = dynamic_cast<XMLElementNode*>(node.get())) 
	{
		for (size_t i = 0; i < elementNode->children().size(); i++)
		{
			convertNodeToWithID(elementNode->children()[i]);
		}	
	}
	/*for (size_t i = 0; i < node->children().size(); i++)
	{
		node->children()[i]->setParent(node);
		if (XMLElementNode* conv = dynamic_cast<XMLElementNode*>(node->children()[i].get()))
		{
			node->children()[i] = new XMLElementNodeWithID(*conv);
			node->children()[i]->setParent(node->parent());
			convertNodeToWithID(node->children()[i]);
		}

	}*/
	//for (int i = 0; i < node->children().size(); i++)
	//{
	//	if (MySharedPtr<XMLElementNode> childAsElementNode = dynamic_cast<XMLElementNode*>(node->children()[i].get()))
	//	{
	//		MySharedPtr<XMLElementNodeWithID> converted = new XMLElementNodeWithID(*childAsElementNode);
	//		//converted->setParent(node);
	//		//delete currentChild;
	//		childAsElementNode = converted;
	//		convertNodeToWithID(childAsElementNode);
	//	}
	//}
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
	setIdToElement(dynamic_cast<XMLElementNodeWithID*>(_root.get()));
	resolveIdConflicts(_root.get());
}

XMLDocumentWithID::XMLDocumentWithID(const XMLDocument& xml)
{
	MySharedPtr<XMLElementNode> newRoot = xml.root();
	//MyWeakPtr<XMLElementNodeWithID> previousParent = newRoot;
	convertNodeToWithID(newRoot);
	_root = newRoot;
	resolveIdConflicts();
}

std::ostream& operator<<(std::ostream& os, const XMLDocumentWithID& doc)
{
	return doc.root()->print(os);
}
