#pragma once
#include <iostream>
#include "..\MyString\MyString.h"
class FileError : public std::runtime_error
{
public:
	FileError() = default;
	explicit FileError(const char* message);
	explicit FileError(const MyString& message);
};