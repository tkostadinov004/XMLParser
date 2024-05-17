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

void XMLRepository::add(const XMLElementNode& item)
{
}

bool XMLRepository::remove(const XMLElementNode& item)
{
    return false;
}

bool XMLRepository::remove(const MyString& id)
{
    return false;
}

const XMLElementNode*& XMLRepository::find(bool(*pred)(XMLElementNode)) const
{
    const XMLElementNode* asd = new XMLElementNode("");
    return asd;
    // TODO: insert return statement here
}
