#include "XMLElementNode.h"
#include "XMLDocument.h"
#include <iomanip>
#include "XMLTextNode.h"
#include "..\..\..\Utils\MyStack\MyStack.hpp"

std::ostream& XMLElementNode::print(std::ostream& os, int indent) const
{
	static int indentationLevel = 0;

	MyString tag = getTagName();
	os << std::setfill(' ') << std::setw(indentationLevel * 3) << "" << "<" << tag;
	if (!this->_attributes.empty())
	{
		os << " " << join(this->_attributes.convertTo<MyString>([](const XMLAttribute& attr) {return attr.getKey() + "=\"" + attr.getValue() + "\"";}));
	}
	if (_children.empty())
	{
		return os << "/>";
	}
	os << ">";
	if (_children.size() == 1)
	{
		_children.back()->print(os);
		os << "</" << tag << ">";
		return os;
	}
	for (size_t i = 0; i < _children.size(); i++)
	{
		os << std::endl;
		indentationLevel++;

		_children[i]->print(os, indentationLevel);
		indentationLevel--;
	}
	os << std::endl << std::setfill(' ') << std::setw(indentationLevel * 3) << "" << "</" << tag << ">";
	return os;
}

XMLElementNode::XMLElementNode(const MyString& tagName, XMLElementNode* parent) : XMLNode(parent)
{
	setTagName(tagName);
}

XMLNode* XMLElementNode::clone() const
{
	return new XMLElementNode(*this);
}

const XMLNamespace* XMLElementNode::getNamespace() const
{
	return _namespace;
}

const MyString& XMLElementNode::getTagName() const
{
	return _tagName;
}

const XMLAttributeCollection& XMLElementNode::attributes() const
{
	return _attributes;
}

const MyVector<PointerWrapper<XMLNode>>& XMLElementNode::children() const
{
	return _children;
}

MyVector<PointerWrapper<XMLNode>>& XMLElementNode::children()
{
	return _children;
}

MyVector<const XMLNode*> XMLElementNode::getDescendants() const
{
	MyVector<const XMLNode*> result;
	MyStack<const XMLNode*> stack;
	stack.push(this);
	while (!stack.empty())
	{
		const XMLNode* popped = stack.pop();
		if (popped != this)
		{
			result.push_back(popped);
		}
		if (const XMLElementNode* parent = dynamic_cast<const XMLElementNode*>(popped))
		{
			for (size_t i = 0; i < parent->children().size(); i++)
			{
				stack.push(parent->children()[i].get());
			}
		}
	}
	return result;
}

MyVector<const XMLNode*> XMLElementNode::getAncestors() const
{
	MyVector<const XMLNode*> result;
	const XMLNode* parent = this->parent();
	while (parent)
	{
		result.push_back(parent);
		parent = parent->parent();
	}
	return result;
}

const MyVector<XMLNamespace>& XMLElementNode::definedNamespaces() const
{
	return _definedNamespaces;
}

const XMLNamespace* XMLElementNode::getDefinedNamespaceByName(const MyString& nsName) const
{
	for (size_t i = 0; i < _definedNamespaces.size(); i++)
	{
		if (_definedNamespaces[i].getKey() == nsName)
		{
			return &_definedNamespaces[i];
		}
	}

	const XMLElementNode* ptr = dynamic_cast<const XMLElementNode*>(parent());
	if (ptr)
	{
		ptr->getDefinedNamespaceByName(nsName);
	}
	return nullptr;
}

void XMLElementNode::setTagName(const MyString& tagName)
{
	this->_tagName = tagName;
}

void XMLElementNode::assignNamespace(const XMLNamespace& ns)
{
	const XMLNamespace* obtained = getDefinedNamespaceByName(ns.getKey());
	if (!obtained)
	{
		throw std::exception(MyString("Namespace \"" + ns.getKey() + "\" is not defined!").c_str());
	}
	this->_namespace = obtained;
}

void XMLElementNode::addAttribute(const XMLAttribute& attribute)
{
	this->_attributes.push_back(attribute);
}

void XMLElementNode::addAttributes(const MyVector<XMLAttribute>& attributes)
{
	for (size_t i = 0; i < attributes.size(); i++)
	{
		const XMLAttribute& current = attributes[i];
		if (current.getKey().starts_with("xmlns"))
		{
			MyString nsName = current.getKey().split(':')[1];
			if (!_definedNamespaces.any([nsName](const XMLNamespace& ns) {return nsName == ns.getKey();}))
			{
				_definedNamespaces.push_back(XMLNamespace(nsName, current.getValue()));
			}
		}
		addAttribute(attributes[i]);
	}
}

void XMLElementNode::changeAttribute(const MyString& attributeName, const MyString& newValue)
{
	if (XMLAttribute* attribute = _attributes[attributeName])
	{
		attribute->setValue(newValue);
	}
}

bool XMLElementNode::deleteAttribute(const MyString& attributeName)
{
	return _attributes.erase([attributeName](const XMLAttribute& attribute) {return attribute.getKey() == attributeName;});
}

bool XMLElementNode::hasTextChild(const MyString& content) const
{
	for (size_t i = 0; i < _children.size(); i++)
	{
		if (const XMLTextNode* textNode = dynamic_cast<const XMLTextNode*>(_children[i].get()))
		{
			if (textNode->textContent() == content)
			{
				return true;
			}
		}
	}
	return false;
}

void XMLElementNode::addChild(XMLNode* child)
{
	child->setParent(this);
	this->_children.push_back(child);
}

void XMLElementNode::addChild(const XMLNode& child)
{
	addChild(child.clone());
}

void XMLElementNode::defineNamespace(XMLNamespace& xmlNamespace)
{
	this->_definedNamespaces.push_back(xmlNamespace);
}
