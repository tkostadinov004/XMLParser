#pragma once
#include "../../../Utils/Readers/Reader.h"

class XPathQueryReader : public Reader
{
	MyString _queryString;
public:
	explicit XPathQueryReader(const MyString& queryString);
	MyVector<MyString> read() const;
};