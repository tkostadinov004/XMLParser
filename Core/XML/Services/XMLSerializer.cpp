#include "XMLSerializer.h"
#include <fstream>

XMLSerializer::XMLSerializer(const MyString& path)
{
    setWorkingPath(path);
}

void XMLSerializer::serialize(const XMLDocument& document)
{
    std::ofstream ofs(_path.c_str());
    ofs << document;
}

const MyString& XMLSerializer::getWorkingPath() const
{
    return _path;
}

void XMLSerializer::setWorkingPath(const MyString& path)
{
    _path = path;
}
