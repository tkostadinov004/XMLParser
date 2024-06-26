#pragma once
#include "Builders/XMLElementNodeBuilder.h"
#include "../../../../../Utils/MyStack/MyStack.hpp"
#include "..\../../Models\XMLTextNode.h"
#include "Builders/XMLTextNodeBuilder.h"
#include "..\..\..\Documents\XMLDocument.h"
class XMLBuildingContext
{
	XMLElementNodeBuilder _elementNodeBuilder;
	XMLTextNodeBuilder _textNodeBuilder;
	MyStack<MyString> _tags;
	MySharedPtr<XMLElementNode> _resultRoot = nullptr;
	MyWeakPtr<XMLElementNode> _previousParent = _resultRoot;
public:
	explicit XMLBuildingContext(DataReader& reader);
	void createTag();
	void createAttributes();
	void createPlainText();
	void closeTag();
	void flushElementNode();
	void flushTextNode();
	XMLDocument finish() const;
};