#include "FileError.h"

FileError::FileError(const char* message) : std::runtime_error(message)
{}
