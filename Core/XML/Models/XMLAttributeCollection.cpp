#include "XMLAttributeCollection.h"

XMLAttributeCollection::XMLAttributeCollection(size_t count) : MyVector(count)
{
}

XMLAttribute* XMLAttributeCollection::operator[](const MyString& attrName)
{
	int index = indexOf([attrName](const XMLAttribute& attr) {return attr.getKey() == attrName;});
	return index != -1 ? &_data[index] : nullptr;
}

const XMLAttribute* XMLAttributeCollection::operator[](const MyString& attrName) const
{
	int index = indexOf([attrName](const XMLAttribute& attr) {return attr.getKey() == attrName;});
	return index != -1 ? &_data[index] : nullptr;
}
