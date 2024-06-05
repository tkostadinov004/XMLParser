#include "XPathQueryDeserializer.h"
#include "..\..\..\Utils\HelperFunctions.h"

XPathQueryComponent XPathQueryDeserializer::parseComponent(const MyString& component) const
{
	MyString componentCopy = component;

	XPathQueryComponent result;
	int axisSeparatorIndex = componentCopy.find("::");
	if (axisSeparatorIndex != -1)
	{
		result.setAxis(componentCopy.substr(0, axisSeparatorIndex));
		componentCopy = componentCopy.substr(axisSeparatorIndex + 2);
	}

	int predicateStartIndex = componentCopy.find("[");
	if (predicateStartIndex != -1)
	{
		MyString tagName = componentCopy.substr(0, predicateStartIndex);
		int nsIndex = tagName.find(":");
		if (nsIndex != -1)
		{
			result.setNamespace(tagName.substr(0, nsIndex));
			result.setTag(tagName.substr(nsIndex + 1));
		}
		else
		{
			result.setTag(tagName);
		}

		componentCopy = componentCopy.substr(predicateStartIndex + 1);

		AttributeFilter filter;
		int comparativeSignIndex = componentCopy.find("=");

		if (comparativeSignIndex != -1)
		{
			filter._isQueryValue = true;
			MyString tag = componentCopy.substr(1, comparativeSignIndex - 1);
			int nsIndex = tag.find(":");
			if (nsIndex != -1)
			{
				filter._key = tag.substr(nsIndex + 1);
				filter._namespace = tag.substr(0, nsIndex);
			}
			else
			{
				filter._key = tag;
			}
			componentCopy = componentCopy.substr(comparativeSignIndex + 1);
			filter._value = componentCopy.substr(1, componentCopy.length() - 3);
		}
		else
		{
			if (componentCopy.starts_with("@"))
			{
				MyString attribute = componentCopy.substr(1).takeWhile([](char c) {return c != ']';});
				int nsIndex = attribute.find(":");
				if (nsIndex != -1)
				{
					filter._key = attribute.substr(nsIndex + 1);
					filter._namespace = attribute.substr(0, nsIndex);
				}
				else
				{
					filter._key = attribute;
				}
			}
			else
			{
				result.setIsIndexDefined(true);
				result.setIndex(HelperFunctions::parseInteger(componentCopy.takeWhile([](char c) {return c != ']';}).c_str()) - 1);
			}
		}
		result.setAttributeFilter(filter);
	}
	else
	{
		MyString tagName = componentCopy;
		int nsIndex = tagName.find(":");
		if (nsIndex != -1)
		{
			result.setNamespace(tagName.substr(0, nsIndex));
			result.setTag(tagName.substr(nsIndex + 1));
		}
		else
		{
			result.setTag(tagName);
		}
	}
	return result;
}

XPathQueryDeserializer::XPathQueryDeserializer(const MyString& queryString) : _reader(queryString) {}

MyVector<XPathQueryComponent> XPathQueryDeserializer::deserialize() const
{
	return _reader.read().convertTo<XPathQueryComponent>([this](const MyString& componentString)
		{
			return parseComponent(componentString);
		});
}
