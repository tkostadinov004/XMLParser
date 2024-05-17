#pragma once
#include <iostream>
#include "..\..\..\Utils\MyString\MyString.h"

class XMLException : public std::logic_error
{
public:
	explicit XMLException(const char* message);
	explicit XMLException(const MyString& message);
};