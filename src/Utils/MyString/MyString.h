#pragma once
#include <iostream>
#include "../MyVector/MyVector.hpp"
#include "..\Iterators\StringIterator.h"

static const size_t npos = -1;
class MyString
{
	char* _data = nullptr;
	size_t _size = 0;
	size_t _capacity = 8;

	void resize(size_t newCapacity);
	void copyFrom(const MyString& other);
	void moveFrom(MyString&& other);
	void free();
	
	MyString(const char* start, const char* end);
public:
	MyString();
	explicit MyString(size_t capacity);
	MyString(const char* str);
	MyString(const MyString& other);
	MyString(MyString&& other) noexcept;
	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other) noexcept;
	~MyString();

	StringIterator begin() const;
	StringIterator end() const;

	char at(int index) const;
	char& operator[](int index);
	const char& operator[](int index) const;
	char& front();
	char& back();
	char front() const;
	char back() const;
	const char* c_str() const;

	bool empty() const;
	size_t length() const;
	size_t capacity() const;
	void shrink_to_fit();

	void clear();
	MyString& insert(char c, int index);
	MyString& insert_range(const MyString& str, int index);
	MyString& insert_range(const char* str, int index);
	void replace(const char* str, int index = 0);
	void replace(const MyString& str, int index = 0);
	void push_back(char c);
	void pop_back();
	MyString& append(char c, size_t count = 1);
	MyString& append(const MyString& str, size_t count = 1);
	MyString& append(const char* str, size_t count = 1);
	MyString& prepend(char c, size_t count = 1);
	MyString& prepend(const MyString& str, size_t count = 1);
	MyString& prepend(const char* str, size_t count = 1);
	MyString& operator+=(const char* str);
	MyString& operator+=(char c);
	MyString& operator+=(const MyString& str);
	MyString takeWhile(bool(*pred)(char)) const;
	MyString skipWhile(bool(*pred)(char)) const;
	MyString trim() const;
	MyString trimStart() const;
	MyString trimEnd() const;
	MyString substr(size_t pos, size_t length = npos) const;
	MyString reverse() const;
	MyString& reverse();
	MyVector<MyString> split(char delim = ' ', bool removeEmptyEntries = false) const;
	MyVector<MyString> split(const MyString& delim, bool removeEmptyEntries = false) const;
	void swap(MyString& other);

	int find(const char* pattern, size_t fromPosition = 0) const;
	int find(const MyString& pattern, size_t fromPosition = 0) const;
	int rfind(const char* pattern, size_t fromPosition = 0) const;
	int rfind(const MyString& pattern, size_t fromPosition = 0) const;

	bool starts_with(const char* pattern) const;
	bool starts_with(const MyString& pattern) const;
	bool ends_with(const char* pattern) const;
	bool ends_with(const MyString& pattern) const;
	bool contains(const char* str) const;
	bool contains(const MyString& str) const;

	friend std::ostream& operator<<(std::ostream& os, const MyString& str);
	friend std::istream& operator>>(std::istream& is, MyString& str);
};
std::istream& getline(std::istream& is, MyString& str, size_t count, char delim = '\n');
MyString join(const MyVector<MyString>& str, const MyString& separator = " ");
MyString toString(int num);

MyString operator+(const MyString& lhs, const MyString& rhs);
MyString operator+(const MyString& lhs, char c);
MyString operator+(char c, const MyString& str);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);
bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);