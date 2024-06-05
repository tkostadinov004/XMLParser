#include "XMLNamespace.h"

XMLNamespace::XMLNamespace(const MyString& name, const MyString& value)
{
	setName(name);
	setValue(value);
}

const MyString& XMLNamespace::getName() const
{
	return _name;
}

void XMLNamespace::setName(const MyString& name)
{
    int namespaceSeparatorIndex = name.find(":");
    if (namespaceSeparatorIndex != -1)
    {
        MyString namespaceName = name.substr(namespaceSeparatorIndex + 1);
        this->_name = namespaceName;
    }
    else
    {
        this->_name = name;
    }
}

const MyString& XMLNamespace::getValue() const
{
	return _value;
}

void XMLNamespace::setValue(const MyString& value)
{
	_value = value;
}
