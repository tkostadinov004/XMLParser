#include "XMLAttribute.h"

XMLAttribute::XMLAttribute(const MyString& key, const MyString& value)
{
    setKey(key);
    setValue(value);
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
    this->_key = key;
}

void XMLAttribute::setValue(const MyString& value)
{
    this->_value = value;
}
