#include <iostream>
#include "HelperFunctions.h"
#include "StringVector.h"

bool HelperFunctions::isPowerOfTwo(unsigned num)
{
	return (num & (num - 1)) == 0;
}

unsigned HelperFunctions::getNextPowerOfTwo(unsigned num)
{
	return isPowerOfTwo(num) ? num << 1 : 1 << (unsigned)ceil(log2(num));
}
static void fillPrefixArray(int* arr, const char* pattern)
{
	if (!arr || !pattern)
	{
		return;
	}

	size_t patternLen = strlen(pattern);
	arr[0] = -1;
	arr[1] = 0;

	int i = 1;
	int prefixLen = 0;

	while (i < patternLen)
	{
		if (pattern[i] == pattern[prefixLen])
		{
			i++;
			prefixLen++;
			arr[i] = prefixLen;
		}
		else if (prefixLen > 0)
		{
			prefixLen = arr[prefixLen];
		}
		else
		{
			i++;
			arr[i] = 0;
		}
	}
}
int HelperFunctions::kmp(const char* pattern, const char* str, bool last)
{
	if (!pattern || !str)
	{
		return -1;
	}
	size_t patternLen = strlen(pattern);
	size_t strLen = strlen(str);

	int* prefixes = new int[patternLen + 1];
	fillPrefixArray(prefixes, pattern);

	int patternIndex = 0;
	int matchIndex = -1;
	for (int i = 0; i < strLen; i++)
	{
		if (pattern[patternIndex] == str[i])
		{
			patternIndex++;
			if (patternIndex == patternLen)
			{
				matchIndex = i - patternIndex + 1;
				if (!last)
				{
					break;
				}
			}
		}
		else
		{
			patternIndex = prefixes[patternIndex];
			if (patternIndex == -1)
			{
				patternIndex++;
			}
		}
	}
	return matchIndex;
}

bool HelperFunctions::isPrefix(const char* str, const char* pattern)
{
	if (!str || !pattern)
	{
		return false;
	}
	while (*str && *pattern)
	{
		if (*str != *pattern)
		{
			return false;
		}
		str++;
		pattern++;
	}
	return !(*pattern);
}

StringVector HelperFunctions::split(const MyString& str, char delimiter)
{
	StringVector arr;
	int index = 0;

	MyString temp;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == delimiter)
		{
			arr.push_back(temp);
			temp.clear();
		}
		temp.append(str[i]);
	}
	arr.push_back(temp);
	return arr;
}
