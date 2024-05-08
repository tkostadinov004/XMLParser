#include <iostream>
#include "HelperFunctions.h"
#include "StringVector.h"
#pragma warning (disable: 4996)

void MyString::resize(size_t newCapacity)
{
	char* temp = _data;
	_data = new char[newCapacity] {0};
	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = temp[i];
	}
	_capacity = newCapacity;
	delete[] temp;
}

void MyString::copyFrom(const MyString& other)
{
	this->_size = other._size;
	this->_capacity = other._capacity;
	this->_data = new char[other._capacity] {0};
	for (size_t i = 0; i < other._size; i++)
	{
		this->_data[i] = other._data[i];
	}
}

void MyString::moveFrom(MyString&& other)
{
	this->_data = other._data;
	other._data = nullptr;
	this->_size = other._size;
	this->_capacity = other._capacity;

	other._size = other._capacity = 0;
}

void MyString::free()
{
	delete[] this->_data;
	this->_data = nullptr;
	this->_size = this->_capacity = 0;
}

MyString::MyString() : MyString("") {}

MyString::MyString(size_t capacity)
{
	this->_data = new char[std::max(8u, HelperFunctions::getNextPowerOfTwo(capacity))];
	this->_capacity = capacity;
}

MyString::MyString(const char* str)
{
	this->_capacity = std::max(8u, HelperFunctions::getNextPowerOfTwo(_size));
	this->_data = new char[_capacity] {0};
	append(str);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString::MyString(MyString&& other) noexcept
{
	moveFrom(std::move(other));
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

MyString& MyString::operator=(MyString&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

MyString::~MyString()
{
	free();
}

char MyString::at(int index) const
{
	if (index < 0 || index >= _size)
	{
		throw std::out_of_range("Index is out of range!");
	}
	return _data[index];
}

char& MyString::operator[](int index)
{
	return _data[index];
}

const char& MyString::operator[](int index) const
{
	return _data[index];
}

char& MyString::front()
{
	if (empty())
	{
		throw std::logic_error("String is empty!");
	}
	return _data[0];
}

char& MyString::back()
{
	if (empty())
	{
		throw std::logic_error("String is empty!");
	}
	return _data[_size - 1];
}

const char* MyString::c_str() const
{
	return _data;
}

bool MyString::empty() const
{
	return _size == 0;
}

size_t MyString::length() const
{
	return _size;
}

size_t MyString::capacity() const
{
	return _capacity;
}

void MyString::shrink_to_fit()
{
	resize(_size + 1);
}

void MyString::clear()
{
	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = 0;
	}
	_size = 0;
}

MyString& MyString::insert(char c, int index)
{
	if (index < 0 || index >= _size)
	{
		throw std::out_of_range("Index is out of range!");
	}
	if (_size + 1 > _capacity)
	{
		resize(std::max(8u, HelperFunctions::getNextPowerOfTwo(_size + 1)));
	}

	for (int i = _size - 1; i >= index; i--)
	{
		_data[i + 1] = _data[i];
	}
	_data[index] = c;
	_size++;
	return *this;
}

MyString& MyString::insert_range(const MyString& str, int index)
{
	return insert_range(str.c_str(), index);
}

MyString& MyString::insert_range(const char* str, int index)
{
	if (!str)
	{
		throw std::invalid_argument("The passed string is invalid!");
	}
	if (index < 0 || index >= _size)
	{
		throw std::out_of_range("Index is out of range!");
	}
	if (str == this->_data)
	{
		char* temp = new char[strlen(this->_data) + 1] {0};
		strcpy(temp, this->_data);
		str = temp;
	}
	size_t inputSize = strlen(str);
	if (_size + inputSize + 1 > _capacity)
	{
		resize(std::max(8u, HelperFunctions::getNextPowerOfTwo(_size + inputSize + 1)));
	}

	for (int i = _size - 1; i >= index; i--)
	{
		_data[i + inputSize] = _data[i];
	}
	for (size_t i = index; i < index + inputSize; i++)
	{
		_data[i] = str[i - index];
	}
	_size += inputSize;
	return *this;
}

void MyString::replace(const char* str, int index)
{
	if (!str)
	{
		throw std::invalid_argument("The passed string is invalid!");
	}
	if (index < 0 || index >= _size)
	{
		throw std::out_of_range("Index is out of range!");
	}
	if (str == this->_data)
	{
		char* temp = new char[strlen(this->_data) + 1] {0};
		strcpy(temp, this->_data);
		str = temp;
	}

	size_t replacementLength = strlen(str);
	if (_size + replacementLength + 1 + index > _capacity)
	{
		resize(std::max(8u, HelperFunctions::getNextPowerOfTwo(_size + replacementLength + 1 + index)));
	}
	for (size_t i = 0; i < replacementLength; i++)
	{
		_data[index + i] = str[i];
	}
}

void MyString::replace(const MyString& str, int index)
{
	replace(str.c_str(), index);
}

void MyString::push_back(char c)
{
	if (_size + 1 > _capacity)
	{
		resize(std::max(8u, HelperFunctions::getNextPowerOfTwo(_size + 1)));
	}
	_data[_size++] = c;
}

void MyString::pop_back()
{
	if (empty())
	{
		throw std::logic_error("String is empty!");
	}
	_size--;
}

MyString& MyString::append(char c, size_t count)
{
	if (_size + 1 + count > _capacity)
	{
		resize(std::max(8u, HelperFunctions::getNextPowerOfTwo(_size + 1 + count)));
	}
	for (size_t i = 0; i < count; i++)
	{
		_data[_size++] = c;
	}

	return *this;
}

MyString& MyString::append(const MyString& str, size_t count)
{
	return append(str.c_str(), count);
}

MyString& MyString::append(const char* str, size_t count)
{
	if (!str)
	{
		throw std::invalid_argument("The passed string is invalid!");
	}
	if (str == this->_data)
	{
		char* temp = new char[strlen(this->_data) + 1] {0};
		strcpy(temp, this->_data);
		str = temp;
	}

	size_t inputSize = strlen(str);
	if (_size + ((inputSize + 1) * count) > _capacity)
	{
		resize(std::max(8u, HelperFunctions::getNextPowerOfTwo(_size + ((inputSize + 1) * count))));
	}
	for (size_t i = 0; i < count; i++)
	{
		for (size_t i = 0; i < inputSize; i++)
		{
			_data[_size++] = str[i];
		}
	}
	return *this;
}

MyString& MyString::operator+=(const char* str)
{
	return append(str);
}

MyString& MyString::operator+=(const MyString& str)
{
	return append(str.c_str());
}

void MyString::swap(MyString& other)
{
	std::swap(this->_data, other._data);
	std::swap(this->_size, other._size);
	std::swap(this->_capacity, other._capacity);
}

int MyString::find(const char* pattern, size_t fromPosition) const
{
	if (!pattern || fromPosition >= _size)
	{
		return -1;
	}
	const char* text = this->c_str();
	text += fromPosition;
	return HelperFunctions::kmp(pattern, text, false);
}

int MyString::find(const MyString& pattern, size_t fromPosition) const
{
	return find(pattern.c_str(), fromPosition);
}

int MyString::rfind(const char* pattern, size_t fromPosition) const
{
	if (!pattern || fromPosition >= _size)
	{
		return -1;
	}
	const char* text = this->c_str();
	text += fromPosition;
	return HelperFunctions::kmp(pattern, text, true);
}

int MyString::rfind(const MyString& pattern, size_t fromPosition) const
{
	return rfind(pattern.c_str(), fromPosition);
}

bool MyString::starts_with(const char* pattern) const
{
	return HelperFunctions::isPrefix(this->c_str(), pattern);
}

bool MyString::starts_with(const MyString& pattern) const
{
	return starts_with(pattern.c_str());
}

bool MyString::ends_with(const char* pattern) const
{
	if (!pattern)
	{
		return false;
	}
	return HelperFunctions::isPrefix(this->c_str() + (_size - strlen(pattern)), pattern);
}

bool MyString::ends_with(const MyString& pattern) const
{
	return ends_with(pattern.c_str());
}

bool MyString::contains(const char* str) const
{
	return find(str, 0) != -1;
}

bool MyString::contains(const MyString& str) const
{
	return contains(str.c_str());
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	return os << str.c_str();
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	size_t currentPos = is.tellg();
	while (!is.eof() && is.get() != '\n')
	{
	}

	size_t count = (size_t)is.tellg() - currentPos;
	char* buffer = new char[count + 1];
	is.clear();
	is.seekg(currentPos);
	is.getline(buffer, count);

	str.replace(buffer);
	return is;
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	MyString result(lhs.length() + rhs.length());
	return result.append(lhs).append(rhs);
}

bool operator<(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}