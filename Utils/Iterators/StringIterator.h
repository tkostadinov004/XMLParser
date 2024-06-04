#pragma once

class StringIterator
{
	char* _ptr;
	size_t _index = 0;
public:
	explicit StringIterator(char* ptr, size_t index);
	char& operator*() const;
	StringIterator& operator++();
	bool operator!=(const StringIterator& other) const;
};