#pragma once
#include "MyString.h"

class StringVector
{
	MyString* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 1;

	void resize(size_t newCapacity);
	void moveFrom(StringVector&& other);
	void copyFrom(const StringVector& other);
	void free();
public:
	StringVector();
	explicit StringVector(size_t capacity);
	StringVector(const MyString* arr, size_t size);
	StringVector(const StringVector& other);
	StringVector(StringVector&& other);
	StringVector& operator=(const StringVector& other);
	StringVector& operator=(StringVector&& other);
	~StringVector();

	void push_back(const MyString& str);
	void push_back(MyString&& str);
	void pop_back();
	void insert(const MyString& str, int index);
	void insert(MyString&& str, int index);
	void erase(int index);
	MyString& operator[](int index);
	const MyString& operator[](int index) const;
	MyString& at(int index);
	const MyString& at(int index) const;
	bool empty() const;
	size_t size() const;
};
std::ostream& operator<<(std::ostream& os, const StringVector& vector);
std::istream& operator>>(std::istream& is, StringVector& vector);