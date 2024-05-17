#include "XMLRepository.h"
#include "..\Services\XMLDeserializer.h"
#include "..\Services\XMLSerializer.h"

void XMLRepository::open(const MyString& path)
{
    XMLDeserializer deserializer(path);
    _xmlDocument = XMLDocumentWithID(deserializer.deserialize());
}

void XMLRepository::close()
{
    _xmlDocument = XMLDocumentWithID();
}

void XMLRepository::saveAs(const MyString& path)
{
    XMLSerializer serializer(path);
    serializer.serializeToStream(XMLDocument(_xmlDocument.root()));
}

void XMLRepository::add(const XMLElementNodeWithID& item)
{
}

bool XMLRepository::remove(const XMLElementNodeWithID& item)
{
    return false;
}

bool XMLRepository::remove(const MyString& id)
{
    return false;
}

const XMLElementNodeWithID*& XMLRepository::find(bool(*pred)(XMLElementNodeWithID)) const
{
    const XMLElementNodeWithID* asd = new XMLElementNodeWithID();
    return asd;
    // TODO: insert return statement here
}
