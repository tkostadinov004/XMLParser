#include "XMLRepository.h"
#include "..\Services\XmlDeserializer.h"

void XMLRepository::open(const MyString& path)
{
    XmlDeserializer deserializer(path);
    _xmlDocument = deserializer.deserialize();
    std::cout << _xmlDocument << std::endl;
}

void XMLRepository::close()
{
}

void XMLRepository::save()
{
}

void XMLRepository::saveas(const MyString& path)
{
}

void XMLRepository::add(const XMLNode& item)
{
}

bool XMLRepository::remove(const XMLNode& item)
{
    return false;
}

bool XMLRepository::remove(const MyString& id)
{
    return false;
}

const XMLNode*& XMLRepository::find(bool(*pred)(XMLNode)) const
{
    const XMLNode* asd = new XMLNode();
    return asd;
    // TODO: insert return statement here
}
