#include "XMLException.h"

XMLException::XMLException(const char* message) : std::logic_error(message)
{
}

XMLException::XMLException(const MyString& message) : XMLException(message.c_str())
{
}
