#include "XPathQueryReader.h"

XPathQueryReader::XPathQueryReader(const MyString& queryString) : _queryString(queryString) {}

MyVector<MyString> XPathQueryReader::read() const
{
    return splitAndIgnore(_queryString, '/', true);
}
