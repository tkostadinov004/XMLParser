#include <iomanip>
#include "XMLElementNode.h"
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
		os << "</" << (this->_namespace ? this->_namespace->getName() + ":" : "") << tag << ">";
		return os;
	}
	for (const MySharedPtr<XMLElementNode>& child : _children)
	{
		os << std::endl;
		indentationLevel++;

		child->print(os, indentationLevel);
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
	for (const MySharedPtr<XMLElementNode>& child : _children)
	{
		result.push_back(child->textContent().trim());
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

const MySharedPtr<XMLNamespace>& XMLElementNode::getNamespace() const
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
			for (const MySharedPtr<XMLElementNode>& child : parent->children())
			{
				stack.push(child.get());
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

const MyVector<MySharedPtr<XMLNamespace>>& XMLElementNode::getNamespacesInScope() const
{
	return _namespacesInScope;
}

const MySharedPtr<XMLNamespace>& XMLElementNode::getNamespaceInScopeByName(const MyString& nsName) const
{
	for (const MySharedPtr<XMLNamespace>& ns : _namespacesInScope)
	{
		if (ns->getName() == nsName)
		{
			return ns;
		}
	}

	MyWeakPtr<XMLElementNode> ptr = this->parent();
	if (ptr)
	{
		return ptr->getNamespaceInScopeByName(nsName);
	}
	return nullptr;
}

void XMLElementNode::setTagName(const MyString& tagName)
{
	this->_tagName = tagName;
}

void XMLElementNode::assignNamespace(const MyString& namespaceName)
{
	MySharedPtr<XMLNamespace> obtained = getNamespaceInScopeByName(namespaceName);
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
	for (const XMLAttribute& attribute : attributes)
	{
		if (attribute.getKey().starts_with("xmlns"))
		{
			MyString nsName = attribute.getKey().split(':')[1];
			if (!_namespacesInScope.any([nsName](const MySharedPtr<XMLNamespace>& ns) {return nsName == ns->getName();}))
			{
				_namespacesInScope.push_back(new XMLNamespace(nsName, attribute.getValue()));
			}
		}
		addAttribute(attribute);
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
		int index = _namespacesInScope.indexOf([&ns](const MySharedPtr<XMLNamespace>& internalNs) {return internalNs->getName() == ns.getName();});
		if (index == -1)
		{
			_namespacesInScope.push_back(new XMLNamespace(ns));
		}
		else
		{
			_namespacesInScope[index]->setValue(ns.getValue());
		}
	}
}

void XMLElementNode::addNamespaces(const MyVector<MySharedPtr<XMLNamespace>>& namespaces)
{
	for (MySharedPtr<XMLNamespace>& ns : namespaces)
	{
		int index = _namespacesInScope.indexOf([&ns](const MySharedPtr<XMLNamespace>& internalNs) {return internalNs->getName() == ns->getName();});
		if (index == -1)
		{
			_namespacesInScope.push_back(ns);
		}
		else
		{
			_namespacesInScope[index]->setValue(ns->getValue());
		}
	}
}

bool XMLElementNode::deleteAttribute(const MyString& attributeName)
{
	return _attributes.erase([attributeName](const XMLAttribute& attribute) {return attribute.getKey() == attributeName;});
}

bool XMLElementNode::hasTextChild(const MyString& content) const
{
	for (const MySharedPtr<XMLElementNode>& child : _children)
	{
		if (const XMLTextNode* textNode = dynamic_cast<const XMLTextNode*>(child.get()))
		{
			if (textNode->textContent() == content)
			{
				return true;
			}
		}
	}
	return false;
}

void XMLElementNode::addChild(const MySharedPtr<XMLNode>& child)
{
	this->_children.push_back(child);
}

void XMLElementNode::addChild(const XMLNode& child)
{
	addChild(child.clone());
}