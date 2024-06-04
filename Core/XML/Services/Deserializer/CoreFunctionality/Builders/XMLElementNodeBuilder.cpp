#include "XMLElementNodeBuilder.h"

XMLElementNodeBuilder::XMLElementNodeBuilder(DataReader& reader) : XMLBuilder(reader)
{
}

void XMLElementNodeBuilder::buildTagName()
{
	MyString tagName = _reader.readTag();
	if (bool isSelfClosing = tagName.ends_with("/"))
	{
		tagName = tagName.substr(0, tagName.length() - 1);
		_tagStatus = TagStatus::SelfClosing;
	}
	if (tagName.contains(":"))
	{
		MyVector<MyString> splittedTag = tagName.split(':');
		_resultObject._namespace = splittedTag[0];
		tagName = splittedTag[1];
	}
	_resultObject._node->setTagName(tagName);
}

const MyString& XMLElementNodeBuilder::getTagName() const
{
	return _resultObject._node->getTagName();
}

MyString XMLElementNodeBuilder::getFullTagName() const
{
	MyString fullTagName;
	if (!_resultObject._namespace.empty())
	{
		fullTagName += _resultObject._namespace + ":";
	}
	fullTagName += _resultObject._node->getTagName();
	return fullTagName;
}

TagStatus XMLElementNodeBuilder::getTagStatus() const
{
	return _tagStatus;
}

void XMLElementNodeBuilder::buildAttributes()
{
	AttributeReaderResult readerAttributes = _reader.readAttributes();
	_resultObject._namespaces = readerAttributes.namespaces;
	_resultObject._attributes = readerAttributes.attributes;
	if (readerAttributes.isTagSelfClosing)
	{
		_tagStatus = TagStatus::SelfClosing;
	}
}

MyString XMLElementNodeBuilder::getClosingTagForValidation()
{
	return _reader.readClosingTag();
}

MySharedPtr<XMLElementNode> XMLElementNodeBuilder::flush(MyWeakPtr<XMLElementNode> parent)
{
	_resultObject._node->setParent(parent);
	if (parent)
	{
		parent->addChild(_resultObject._node);
	}

	MyWeakPtr<XMLElementNode> target = _resultObject._node;
	MyVector<XMLNamespace> namespaces = _resultObject._namespaces.convertTo<XMLNamespace>([](const DeserializedAttribute& attr)
		{
			return XMLNamespace(attr._key, attr._value);
		});
	_resultObject._node->addNamespaces(namespaces);
	_resultObject._node->addAttributes(_resultObject._namespaces.convertTo<XMLAttribute>([target](const DeserializedAttribute& attr)
		{
			return XMLAttribute(attr._key, attr._value, "", target);
		}));
	
	MyVector<XMLAttribute> attributes = _resultObject._attributes.convertTo<XMLAttribute>([target](const DeserializedAttribute& attr)
		{
			return XMLAttribute(attr._key, attr._value, attr._namespaceName, target);
		});
	_resultObject._node->addAttributes(attributes);

	if (!_resultObject._namespace.empty())
	{
		_resultObject._node->assignNamespace(_resultObject._namespace);
	}	

	MySharedPtr<XMLElementNode> result = _resultObject._node;
	_resultObject = TemporaryBuildingObject();
	_tagStatus = TagStatus::Open;
	return result;
}
