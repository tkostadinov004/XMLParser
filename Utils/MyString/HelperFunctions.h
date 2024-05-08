#pragma once
#include "StringVector.h"
namespace HelperFunctions
{
	bool isPowerOfTwo(unsigned num);
	unsigned getNextPowerOfTwo(unsigned num);
	int kmp(const char* pattern, const char* str, bool last);
	bool isPrefix(const char* str, const char* pattern);
	StringVector split(const MyString& str, char delimiter = ' ');
}