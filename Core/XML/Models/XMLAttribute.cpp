#include "XMLAttribute.h"
#include "XMLElementNode.h"
#include "..\..\..\Utils\Messages\ErrorMessageBuilder.h"

XMLAttribute::XMLAttribute(const MyString& key, const MyString& value)
{
    setKey(key);
    setValue(value);
}

XMLAttribute::XMLAttribute(const MyString& key, const MyString& value, const MyString& namespaceName, const MyWeakPtr<XMLElementNode>& owner) : XMLAttribute(key, value)
{
    setOwner(owner);
    assignNamespace(namespaceName); 
}

const MyString& XMLAttribute::getKey() const
{
    return _key;
}

const MyString& XMLAttribute::getValue() const
{
    return _value;
}

void XMLAttribute::setKey(const MyString& key)
{
    //if (key.empty())
    //{
    //    throw std::invalid_argument(ErrorMessageBuilder::ATTRIBUTE_NAME_EMPTY());
    //}

    int namespaceSeparatorIndex = key.find(":");
    if (namespaceSeparatorIndex != -1)
    {
        MyString namespaceName = key.substr(0, namespaceSeparatorIndex);
        if (namespaceName == "xmlns")
        {
            this->_key = key;
            return;
        }
        MyString attributeName = key.substr(namespaceSeparatorIndex + 1);
        assignNamespace(namespaceName);
        this->_key = attributeName;
    }
    else
    {
        this->_key = key;
    }
}

void XMLAttribute::setValue(const MyString& value)
{
    this->_value = value;
}

const MySharedPtr<XMLNamespace>& XMLAttribute::getNamespace() const
{
    return _namespace;
}

void XMLAttribute::assignNamespace(const MyString& namespaceName)
{
    if (namespaceName.empty())
    {
        return;
    }

    MyWeakPtr<XMLElementNode> owner = _owner;
    MySharedPtr<XMLNamespace> obtained = owner->getDefinedNamespaceByName(namespaceName);
    if (!obtained)
    {
        throw std::exception(MyString("Namespace \"" + namespaceName + "\" is not defined!").c_str());
    }
    this->_namespace = obtained;
}

const MyWeakPtr<XMLElementNode>& XMLAttribute::getOwner() const
{
    return _owner;
}

void XMLAttribute::setOwner(const MyWeakPtr<XMLElementNode>& node)
{
    _owner = node;
}

MyString XMLAttribute::toString() const
{
    return MyString((_namespace ? _namespace->getName() + ":" : "") + _key + "=\"" + _value + "\"");
}
