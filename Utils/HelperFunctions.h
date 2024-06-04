#pragma once
#include <cstdint>
#include "MyString\MyString.h"
namespace HelperFunctions
{
	int32_t parseInteger(const char* str);
	int32_t parseInteger(const MyString& str);
}