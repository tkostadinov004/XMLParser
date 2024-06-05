#pragma once
#include "..\../../../Models\XMLElementNode.h"
#include "../DataReader.h"
#include "XMLBuilder.hpp"
enum class TagStatus
{
	Open,
	SelfClosing
};
struct TemporaryBuildingObject
{
	MySharedPtr<XMLElementNode> _node;
	MyString _namespace;
	MyVector<DeserializedAttribute> _attributes;
	MyVector<DeserializedAttribute> _namespaces;
	TemporaryBuildingObject()
	{
		_node = new XMLElementNode();
	}
};
class XMLElementNodeBuilder : public XMLBuilder<XMLElementNode>
{
	TemporaryBuildingObject _resultObject;
	TagStatus _tagStatus = TagStatus::Open;
public:
	explicit XMLElementNodeBuilder(DataReader& reader);
	void buildTagName();
	const MyString& getTagName() const;
	MyString getFullTagName() const;
	TagStatus getTagStatus() const;
	void buildAttributes();
	MyString getClosingTagForValidation();
	MySharedPtr<XMLElementNode> flush(MyWeakPtr<XMLElementNode> parent) override;
};