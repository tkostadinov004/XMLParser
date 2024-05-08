#pragma once
#include <iostream>
class FileError : public std::runtime_error
{
public:
	FileError() = default;
	explicit FileError(const char* message);
};