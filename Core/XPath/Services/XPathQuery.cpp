#include "XPathQuery.h"
#include "..\..\XML\Models\XMLTextNode.h"
#include "..\QueryParser\XPathQueryDeserializer.h"
#include "XPathSelectorFactory.h"

MyVector<MyString> XPathQuery::evaluate(const MySharedPtr<XMLElementNode> root, const MyString& queryString)
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

	return result.convertTo<MyString>([](const XMLNode* node)
		{
			return MyString("\"" + node->textContent() + "\"");
		});
}
