#pragma once
#include "..\Models\XPathQueryComponent.h"
#include "XPathQueryReader.h"
class XPathQueryDeserializer
{
	XPathQueryReader _reader;

	XPathQueryComponent parseComponent(const MyString& component) const;
public:
	explicit XPathQueryDeserializer(const MyString& queryString);
	MyVector<XPathQueryComponent> deserialize() const;
};