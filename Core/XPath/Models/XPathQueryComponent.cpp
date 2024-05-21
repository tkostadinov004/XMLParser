#include "XPathQueryComponent.h"

const MyString& XPathQueryComponent::getAxis() const
{
    return _axis;
}

void XPathQueryComponent::setAxis(const MyString& axis)
{
    _axis = axis;
}

const MyString& XPathQueryComponent::getTag() const
{
    return _tag;
}

void XPathQueryComponent::setTag(const MyString& tag)
{
    _tag = tag;
}

int XPathQueryComponent::getIndex() const
{
    return _index;
}

void XPathQueryComponent::setIndex(size_t index)
{
    _index = index;
}

const AttributeFilter& XPathQueryComponent::getAttributeFilter() const
{
    return _attributeFilter;
}

void XPathQueryComponent::setAttributeFilter(const AttributeFilter& attributeFilter)
{
    _attributeFilter = attributeFilter;
}

const MyString& XPathQueryComponent::getAttributeExists() const
{
    return _attributeExists;
}

void XPathQueryComponent::setAttributeExists(const MyString& attributeExists)
{
    _attributeExists = attributeExists;
}
