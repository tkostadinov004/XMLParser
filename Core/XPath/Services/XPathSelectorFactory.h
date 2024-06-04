#pragma once
#include "..\Models\XPathQueryComponent.h"
#include "../../../Utils/MySharedPtr/MySharedPtr.hpp"
#include "..\Selectors\XPathSelector.h"
class XPathSelectorFactory
{
	XPathQueryComponent _component;
public:
	explicit XPathSelectorFactory(const XPathQueryComponent& component);
	MySharedPtr<XPathSelector> create() const;
};