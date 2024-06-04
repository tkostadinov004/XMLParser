#include "HelperFunctions.h"

int32_t HelperFunctions::parseInteger(const char* str)
{
	if (!str)
	{
		throw std::invalid_argument("Parsing invalid string!");
	}

	bool isNegative = *str == '-';
	if (isNegative)
	{
		str++;
	}

	long long result = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			(result *= 10) += *str - '0';
			if (result > INT32_MAX)
			{
				return isNegative ? INT32_MIN : INT32_MAX;
			}
		}
		else
		{
			throw std::invalid_argument("Parsing invalid string!");
		}
		str++;
	}
	return isNegative ? -result : result;
}

int32_t HelperFunctions::parseInteger(const MyString& str)
{
	return parseInteger(str.c_str());
}
