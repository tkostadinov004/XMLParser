#include "XPathQuery.h"
#include "..\..\XML\Models\XMLTextNode.h"
#include "..\QueryParser\XPathQueryDeserializer.h"
#include "XPathSelectorFactory.h"
#include "..\ResultSerializers\XPathQueryResultSerializer.h"

MyVector<const XMLNode*> XPathQuery::evaluate(const MySharedPtr<XMLElementNode> root, const MyString& queryString)
{
	MyVector<const XMLNode*> result;
	result.push_back(root.get());

	XPathQueryDeserializer deserializer(queryString);
	MyVector<XPathQueryComponent> components = deserializer.deserialize();

	for (const XPathQueryComponent& currentComponent : components)
	{
		XPathSelectorFactory factory(currentComponent);
		result = factory.create()->execute(result, currentComponent);
	}

	return result;
}
