#pragma once
#include "XMLBuilder.hpp"
#include "..\../../../Models\XMLTextNode.h"
#include "..\../../../Models\XMLElementNode.h"
class XMLTextNodeBuilder : public XMLBuilder<XMLTextNode>
{
	MySharedPtr<XMLTextNode> _node = nullptr;
public:
	explicit XMLTextNodeBuilder(DataReader& reader);
	void buildContent();
	MySharedPtr<XMLTextNode> flush(MyWeakPtr<XMLElementNode> parent) override;
};