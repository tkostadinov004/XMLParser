#include "StringIterator.h"

StringIterator::StringIterator(char* ptr, size_t index) : _ptr(ptr), _index(index) {}

char& StringIterator::operator*() const
{
	return *(_ptr + _index);
}

StringIterator& StringIterator::operator++()
{
	_index++;
	return *this;
}

bool StringIterator::operator!=(const StringIterator& other) const
{
	return _index != other._index;
}