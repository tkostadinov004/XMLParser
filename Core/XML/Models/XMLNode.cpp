#include "XMLNode.h"
#include "XMLDocument.h"
#include <iomanip>

std::ostream& XMLNode::print(std::ostream& os) const
{
	static int level = 0;
	level++;
	os << '<';
	if (getNamespace())
	{
		os << getNamespace()->getKey() << ":";
	}
	os << getTagName();
	for (size_t i = 0; i < attributes().size(); i++)
	{
		os << " " << attributes()[i].getKey() << "=" << "\"" << attributes()[i].getValue() << "\" ";
	}
	os << ">";
	if (!children().empty())
	{
		os << std::endl;
	}
	if (!textContent().empty())
	{
		if (!children().empty())
		{
			os << std::setfill('\t') << std::setw(level) << "";
		}
		os << textContent();
		if (!children().empty())
		{
			os << std::endl;
		}
	}
	for (size_t i = 0; i < children().size(); i++)
	{
		if (!children().empty())
		{
			os << std::setfill('\t') << std::setw(level) << "";
		}
		os << *children()[i] << std::endl;
		level--;
	}
	if (!children().empty())
	{
		os << std::setfill('\t') << std::setw(level - 1) << "";
	}
	os << '<' << '/' << getTagName() << '>';

	return os;
}

XMLNode::XMLNode(const MyString& tagName, XMLNode* parent)
{
	setTagName(tagName);
	this->_parent = parent;
}

const XMLNamespace* XMLNode::getNamespace() const
{
	return _namespace;
}

const MyString& XMLNode::getTagName() const
{
	return _tagName;
}

XMLNode* XMLNode::parent()
{
	return _parent;
}

const MyVector<XMLAttribute>& XMLNode::attributes() const
{
	return _attributes;
}

const MyVector<XMLElement*>& XMLNode::children() const
{
	return _children;
}

const MyVector<XMLNamespace>& XMLNode::definedNamespaces() const
{
	return _definedNamespaces;
}

bool XMLNode::canHaveNamespace(const MyString& nsName) const
{
	for (size_t i = 0; i < _definedNamespaces.size(); i++)
	{
		if (_definedNamespaces[i].getKey() == nsName)
		{
			return true;
		}
	}

	if (this->_parent)
	{
		this->_parent->canHaveNamespace(nsName);
	}
	return false;
}

void XMLNode::setTagName(const MyString& tagName)
{
	this->_tagName = tagName;
}

void XMLNode::setParent(XMLNode* parent)
{
	this->_parent = parent;
}

void XMLNode::setNamespace(const XMLNamespace& xmlNamespace)
{
	this->_namespace = &xmlNamespace;
}

void XMLNode::addAttribute(const XMLAttribute& attribute)
{
	this->_attributes.push_back(attribute);
}

void XMLNode::addAttributes(const MyVector<XMLAttribute>& attributes)
{
	for (size_t i = 0; i < attributes.size(); i++)
	{
		const XMLAttribute& current = attributes[i];
		if (current.getKey().starts_with("xmlns"))
		{
			MyString nsName = current.getKey().split(':')[1];
			if (!_definedNamespaces.any<MyString>([nsName](const MyString& name) {return nsName == name;}))
			{
				_definedNamespaces.push_back(XMLNamespace(nsName, current.getValue()));
			}
		}
		addAttribute(attributes[i]);
	}
}

void XMLNode::addChild(XMLElement* child)
{
	this->_children.push_back(child);
}

void XMLNode::defineNamespace(XMLNamespace& xmlNamespace)
{
	this->_definedNamespaces.push_back(xmlNamespace);
}
