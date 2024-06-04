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

const MyString& XPathQueryComponent::getNamespace() const
{
    return _namespace;
}

void XPathQueryComponent::setNamespace(const MyString& ns)
{
    _namespace = ns;
}

bool XPathQueryComponent::isIndexDefined() const
{
    return _isIndexDefined;
}
void XPathQueryComponent::setIsIndexDefined(bool isIndexDefined)
{
    _isIndexDefined = isIndexDefined;
}

int XPathQueryComponent::getIndex() const
{
    return _index;
}

void XPathQueryComponent::setIndex(int index)
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
