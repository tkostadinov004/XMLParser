#include "XMLSerializer.h"
#include <fstream>
#include "..\..\..\Utils\Exceptions\FileError.h"
#include "..\..\..\Utils\Messages\ErrorMessageBuilder.h"

XMLSerializer::XMLSerializer(const MyString& path)
{
    setWorkingPath(path);
}

void XMLSerializer::serializeToStream(const XMLDocument& document)
{
    std::ofstream ofs(_path.c_str());
    if (!ofs.is_open())
    {
        throw FileError(ErrorMessageBuilder::ERROR_OPENING_FILE(_path));
    }
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
