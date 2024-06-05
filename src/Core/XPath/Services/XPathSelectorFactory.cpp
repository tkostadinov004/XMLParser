#include "XPathSelectorFactory.h"
#include "../Selectors/XPathMixinSelector.h"
#include "../Selectors/AxisSelectors/XPathAncestorSelector.h"
#include "../Selectors/AxisSelectors/XPathAxisSelector.h"
#include "../Selectors/AxisSelectors/XPathChildSelector.h"
#include "../Selectors/AxisSelectors/XPathDescendantSelector.h"
#include "../Selectors/AxisSelectors/XPathParentSelector.h"
#include "../Selectors/AttributeSelectors/XPathAttributeByExistenceSelector.h"
#include "../Selectors/AttributeSelectors/XPathAttributeByValueSelector.h"

XPathSelectorFactory::XPathSelectorFactory(const XPathQueryComponent& component) : _component(component)
{
}

MySharedPtr<XPathSelector> XPathSelectorFactory::create() const
{
	MySharedPtr<XPathSelector> result;
	if (_component.getAxis() == "child")
	{
		result = new XPathChildSelector();
	}
	else if (_component.getAxis() == "descendant")
	{
		result = new XPathDescendantSelector();
	}
	else if (_component.getAxis() == "parent")
	{
		result = new XPathParentSelector();
	}
	else if (_component.getAxis() == "ancestor")
	{
		result = new XPathAncestorSelector();
	}

	if (_component.getAttributeFilter()._isQueryValue && !_component.getAttributeFilter()._key.empty())
	{
		result = new XPathMixinSelector(result, new XPathAttributeByValueSelector());
	}
	else if (!_component.getAttributeFilter()._key.empty() && !_component.getAttributeFilter()._isQueryValue)
	{
		result = new XPathMixinSelector(result, new XPathAttributeByExistenceSelector());
	}
    return result;
}