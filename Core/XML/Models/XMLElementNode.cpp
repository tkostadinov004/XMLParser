#include "XMLElementNode.h"
#include "XMLDocument.h"
#include <iomanip>
#include "XMLTextNode.h"
#include "..\..\..\Utils\MyStack\MyStack.hpp"

std::ostream& XMLElementNode::print(std::ostream& os, int indent) const
{
	static int indentationLevel = 0;

	MyString tag = getTagName();
	os << std::setfill(' ') << std::setw(indentationLevel * 3) << "" << "<";
	if (this->_namespace)
	{
		os << this->_namespace->getName() << ':';
	}
	os << this->getTagName();
	if (!this->_attributes.empty())
	{
		os << " " << join(this->_attributes.convertTo<MyString>([](const XMLAttribute& attr) {return attr.toString();}));
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
	os << std::endl << std::setfill(' ') << std::setw(indentationLevel * 3) << "" << "</";
	if (this->_namespace)
	{
		os << this->_namespace->getName() << ':';
	}
	os << tag << ">";
	return os;
}

MyString XMLElementNode::textContent() const
{
	MyVector<MyString> result;
	for (size_t i = 0; i < _children.size(); i++)
	{
		result.push_back(_children[i]->textContent().trim());
	}
	return join(result);
}

XMLElementNode::XMLElementNode(const MyString& tagName)
{
	setTagName(tagName);
}

MySharedPtr<XMLNode> XMLElementNode::clone() const
{
	return new XMLElementNode(*this);
}

MySharedPtr<XMLNamespace> XMLElementNode::getNamespace() const
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

const MyVector<MySharedPtr<XMLNode>>& XMLElementNode::children() const
{
	return _children;
}

MyVector<MySharedPtr<XMLNode>>& XMLElementNode::children()
{
	return _children;
}

MyVector<MySharedPtr<const XMLNode>> XMLElementNode::getDescendants() const
{
	MyVector<MySharedPtr<const XMLNode>> result;
	MyStack<const XMLNode*> stack;
	stack.push(this);
	while (!stack.empty())
	{
		const XMLNode* popped = stack.peek();
		stack.pop();
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

MyVector<MyWeakPtr<XMLElementNode>> XMLElementNode::getAncestors() const
{
	MyVector<MyWeakPtr<XMLElementNode>> result;
	MyWeakPtr<XMLElementNode> parent = this->parent();
	while (parent)
	{
		result.push_back(parent);
		parent = parent->parent();
	}
	return result;
}

const MyVector<MySharedPtr<XMLNamespace>>& XMLElementNode::definedNamespaces() const
{
	return _definedNamespaces;
}

MySharedPtr<XMLNamespace> XMLElementNode::getDefinedNamespaceByName(const MyString& nsName) const
{
	for (size_t i = 0; i < _definedNamespaces.size(); i++)
	{
		if (_definedNamespaces[i]->getName() == nsName)
		{
			return _definedNamespaces[i];
		}
	}

	MyWeakPtr<XMLElementNode> ptr = this->parent();
	if (ptr)
	{
		return ptr->getDefinedNamespaceByName(nsName);
	}
	return nullptr;
}

void XMLElementNode::setTagName(const MyString& tagName)
{
	this->_tagName = tagName;
}

void XMLElementNode::assignNamespace(const MyString& namespaceName)
{
	MySharedPtr<XMLNamespace> obtained = getDefinedNamespaceByName(namespaceName);
	if (!obtained)
	{
		throw std::exception(MyString("Namespace \"" + namespaceName + "\" is not defined!").c_str());
	}
	this->_namespace = obtained;
}
void XMLElementNode::addAttribute(const XMLAttribute& attribute)
{
	XMLAttribute attr = attribute;
	attr.setOwner(this);
	this->_attributes.push_back(attr);
}

void XMLElementNode::addAttributes(const MyVector<XMLAttribute>& attributes)
{
	for (size_t i = 0; i < attributes.size(); i++)
	{
		const XMLAttribute& current = attributes[i];
		if (current.getKey().starts_with("xmlns"))
		{
			MyString nsName = current.getKey().split(':')[1];
			if (!_definedNamespaces.any([nsName](const MySharedPtr<XMLNamespace>& ns) {return nsName == ns->getName();}))
			{
				_definedNamespaces.push_back(new XMLNamespace(nsName, current.getValue()));
			}
		}
		addAttribute(attributes[i]);
	}
}

void XMLElementNode::changeAttribute(const MyString& attributeName, const MyString& newValue)
{
	if (MySharedPtr<XMLAttribute> attribute = _attributes[attributeName])
	{
		attribute->setValue(newValue);
	}
}

void XMLElementNode::addNamespaces(const MyVector<XMLNamespace>& namespaces)
{
	for (const XMLNamespace& ns : namespaces)
	{
		int index = _definedNamespaces.indexOf([&ns](const MySharedPtr<XMLNamespace>& internalNs) {return internalNs->getName() == ns.getName();});
		if (index == -1)
		{
			_definedNamespaces.push_back(new XMLNamespace(ns));
		}
		else
		{
			_definedNamespaces[index]->setValue(ns.getValue());
		}
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

void XMLElementNode::addChild(MySharedPtr<XMLNode> child)
{
	this->_children.push_back(child);
}

void XMLElementNode::addChild(const XMLNode& child)
{
	addChild(child.clone());
}
//
//void XMLElementNode::defineNamespace(XMLNamespace& xmlNamespace)
//{
//	this->_definedNamespaces.push_back(xmlNamespace);
//}
