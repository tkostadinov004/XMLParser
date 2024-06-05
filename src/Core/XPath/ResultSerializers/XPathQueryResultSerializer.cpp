#include "XPathQueryResultSerializer.h"

MyString XPathQueryResultSerializer::serializeResult(const MyVector<const XMLNode*>& result) const
{
	MyString serializationResult;
	for (int i = 0; i < result.size(); i++)
	{
		serializationResult.append(toString(i + 1) + ".\t");
		serializationResult.append(result[i]->textContent());
		serializationResult.append("\n");
	}
	return serializationResult;
}
