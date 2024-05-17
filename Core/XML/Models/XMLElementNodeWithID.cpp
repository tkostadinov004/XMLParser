#include "XMLElementNodeWithID.h"
GroupVector XMLElementNodeWithID::idGroups;

XMLElementNodeWithID::XMLElementNodeWithID(const MyString& tagName, const MyString& id, XMLElementNodeWithID* parent) : XMLElementNode(tagName, parent)
{
}

XMLElementNodeWithID::XMLElementNodeWithID(const XMLElementNode& node) : XMLElementNode(node)
{
	/*XMLAttribute* idAttribute = _attributes["id"];
	if (idAttribute)
	{
		const MyString& id = idAttribute->getKey();
		this->_id = id;
		if (idGroups[id] > 0)
		{
			this->_id += "_" + toString(idGroups[id]++);
			idAttribute->setValue(this->_id);
		}
		else
		{
			idGroups.add(id);
		}
	}*/
}

const MyString& XMLElementNodeWithID::getId() const
{
	const XMLAttribute* idPtr = _attributes["id"];
	return idPtr ? idPtr->getKey() : "";
}

void XMLElementNodeWithID::setid(const MyString& id)
{
	XMLAttribute* idAttribute = _attributes["id"];
	if (idAttribute)
	{
		const MyString& id = idAttribute->getKey();
		if (idGroups[id] > 0)
		{
			idAttribute->setValue(idAttribute->getKey() + "_" + toString(idGroups[id]++));
		}
		else
		{
			idGroups.add(id);
		}
	}
}
