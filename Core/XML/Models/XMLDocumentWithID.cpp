#include "XMLDocumentWithID.h"
#include "..\..\..\Utils\MyStack\MyStack.hpp"
#include "XMLTextNode.h"

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
static MySharedPtr<XMLElementNodeWithID> copy(const MySharedPtr<XMLElementNode>& node, const MyWeakPtr<XMLElementNodeWithID>& parent)
{
	MySharedPtr<XMLElementNode> result = new XMLElementNodeWithID();
	MyVector<MySharedPtr<XMLNamespace>> nss = node->definedNamespaces().convertTo<MySharedPtr<XMLNamespace>>([](const MySharedPtr<XMLNamespace>& ns) 
		{
			return new XMLNamespace(*ns);
		});
	result->setParent(parent);
	result->addNamespaces(nss);
	if (node->getNamespace())
	{
		result->assignNamespace(node->getNamespace()->getName());
	}
	result->setTagName(node->getTagName());
	result->addAttributes(node->attributes().convertTo<XMLAttribute>([&result](const XMLAttribute& attr)
	{
			return XMLAttribute(attr.getKey(), attr.getValue(), (attr.getNamespace() ? attr.getNamespace()->getName() : ""), MyWeakPtr<XMLElementNode>(result));
	}));
	return result;
}
MySharedPtr<XMLElementNode> XMLDocumentWithID::convertNodeToWithID(const MySharedPtr<XMLElementNode>& src, const MyWeakPtr<XMLElementNodeWithID>& parent)
{
	if (!parent || !src)
	{
		return nullptr;
	}
	if (const XMLTextNode* text = dynamic_cast<const XMLTextNode*>(dynamic_cast<XMLNode*>(src.get())))
	{
		MySharedPtr<XMLTextNode> dest = new XMLTextNode(text->textContent());
		dest->setParent(parent);
		return dest;
	}

	MySharedPtr<XMLElementNodeWithID> dest = copy(src, parent);
	for (size_t i = 0; i < src->children().size(); i++)
	{
		dest->addChild(convertNodeToWithID(src->children()[i], dest));
	}
	return dest;
}

void XMLDocumentWithID::resolveIdConflicts()
{
	if (!_root)
	{
		return;
	}
	setIdToElement(dynamic_cast<XMLElementNodeWithID*>(_root.get()));
	resolveIdConflicts(_root.get());
}

XMLDocumentWithID::XMLDocumentWithID(const XMLDocument& xml)
{
	_root = new XMLElementNodeWithID();
	MyWeakPtr<XMLElementNode> previousParent = _root;
	MySharedPtr<XMLElementNode> tempresult = convertNodeToWithID(xml.root(), previousParent);
	_root = tempresult;
	resolveIdConflicts();
}

std::ostream& operator<<(std::ostream& os, const XMLDocumentWithID& doc)
{
	return doc.root()->print(os);
}
