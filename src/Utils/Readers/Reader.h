#pragma once
#include "..\MyString\MyString.h"
#include "..\MyVector\MyVector.hpp"
class Reader
{
public:
	MyVector<MyString> splitAndIgnore(const MyString& str, char delim = ' ', bool removeEmptyEntries = false) const;
};