#include "FileError.h"

FileError::FileError(const char* message) : std::runtime_error(message)
{}

FileError::FileError(const MyString& message) : FileError(message.c_str())
{
}
