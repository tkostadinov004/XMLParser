#pragma once
#include <iostream>
#include <functional>
#include "../Iterator.hpp"

namespace HelperFunctions
{
	static bool isPowerOfTwo(unsigned num);
	static unsigned getNextPowerOfTwo(unsigned num);
}
template <typename T>
class MyVector
{
protected:
	T* _data;
	size_t _size = 0;
	size_t _capacity = 1;
private:
	void copyFrom(const MyVector& other);
	void moveFrom(MyVector&& other);
	void free();
	void resize(size_t capacity);

	void shiftLeft(int index, size_t size);
	void shiftRight(int index, size_t size);
public:
	MyVector();
	explicit MyVector(size_t count);
	MyVector(const MyVector& other);
	MyVector(MyVector<T>&& other);
	MyVector<T>& operator=(const MyVector& other);
	MyVector<T>& operator=(MyVector&& other);
	~MyVector();
	
	Iterator<T> begin() const;
	Iterator<T> end() const;

	size_t size() const;
	size_t capacity() const;

	T& at(int index);
	const T& at(int index) const;
	T& operator[](int index);
	const T& operator[](int index) const;
	T& front();
	const T& front() const;
	T front_or_default() const;
	T& back();
	const T& back() const;
	T back_or_default() const;

	bool contains(const T& element) const;
	bool any(std::function<bool(const T&)> pred) const;
	int indexOf(const T& element) const;
	int indexOf(std::function<bool(const T&)> pred) const;
	size_t count(std::function<bool(const T&)> pred) const;
	MyVector<T> filter(std::function<bool(const T&)> pred) const;
	bool empty() const;
	void shrink_to_fit();
	void clear();
	void insert(int index, const T& element);
	void insert(int index, T&& element);
	void insert_range(int index, const MyVector& vector);
	void insert_range(int index, MyVector&& vector);
	void erase(int index);
	void erase(int start, int end);
	bool erase(std::function<bool(const T&)> pred);
	void push_back(const T& element);
	void push_back(T&& element);
	void append(const T& element, size_t count = 1);
	void append(T&& element, size_t count = 1);
	void append_range(const MyVector& vector);
	void append_range(MyVector&& vector);
	void pop_back();

	template <typename _Out>
	MyVector<_Out> convertTo(std::function<_Out(const T&)> selector) const;
};
template <typename T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& vector);
template <typename T>
bool operator==(const MyVector<T>& lhs, const MyVector<T>& rhs);
template <typename T>
bool operator!=(const MyVector<T>& lhs, const MyVector<T>& rhs);
template <typename T>
bool operator<(const MyVector<T>& lhs, const MyVector<T>& rhs);
template <typename T>
bool operator<=(const MyVector<T>& lhs, const MyVector<T>& rhs);
template <typename T>
bool operator>(const MyVector<T>& lhs, const MyVector<T>& rhs);
template <typename T>
bool operator>=(const MyVector<T>& lhs, const MyVector<T>& rhs);

static bool HelperFunctions::isPowerOfTwo(unsigned num)
{
	return (num & (num - 1)) == 0;
}

static unsigned HelperFunctions::getNextPowerOfTwo(unsigned num)
{
	num |= num >> 1;
	num |= num >> 2;
	num |= num >> 4;
	num |= num >> 8;
	num |= num >> 16;
	return num + 1;
}

template<typename T>
void MyVector<T>::copyFrom(const MyVector<T>& other)
{
	this->_size = other._size;
	this->_capacity = other._capacity;
	this->_data = new T[other._capacity];
	for (size_t i = 0; i < other._capacity; i++)
	{
		this->_data[i] = other._data[i];
	}
}

template<typename T>
void MyVector<T>::moveFrom(MyVector<T>&& other)
{
	this->_size = other._size;
	this->_capacity = other._capacity;
	this->_data = other._data;

	other._data = nullptr;
	other._size = other._capacity = 0;
}

template<typename T>
void MyVector<T>::free()
{
	delete[] _data;
	_size = 0;
}

template<typename T>
void MyVector<T>::resize(size_t capacity)
{
	T* temp = _data;
	_data = new T[capacity];
	if (capacity < _size)
	{
		_size = capacity;
	}
	for (size_t i = 0; i < _size; i++)
	{
		_data[i] = temp[i];
	}
	delete[] temp;
	_capacity = capacity;

}

template<typename T>
void MyVector<T>::shiftLeft(int index, size_t size)
{
	for (size_t i = index; i < _size - size; i++)
	{
		_data[i] = _data[i + size];
	}
	_size -= size;

	if (_size * 4 <= _capacity && _capacity > 1)
	{
		resize(_capacity / 2);
	}
}

template<typename T>
void MyVector<T>::shiftRight(int index, size_t size)
{
	if (_size + size > _capacity)
	{
		resize(HelperFunctions::getNextPowerOfTwo(_size + size));
	}

	for (int i = _size - 1; i >= index; i--)
	{
		_data[i + size] = _data[i];
	}
	_size += size;
}

template<typename T>
MyVector<T>::MyVector() : MyVector(1) {}

template<typename T>
MyVector<T>::MyVector(size_t count)
{
	this->_capacity = count;
	this->_data = new T[count];
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other)
{
	copyFrom(other);
}

template<typename T>
MyVector<T>::MyVector(MyVector<T>&& other)
{
	moveFrom(std::move(other));
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
Iterator<T> MyVector<T>::begin() const
{
	return Iterator<T>(0, _data);
}

template<typename T>
Iterator<T> MyVector<T>::end() const
{
	return Iterator<T>(_size, _data);
}

template<typename T>
MyVector<T>::~MyVector()
{
	free();
}

template<typename T>
size_t MyVector<T>::size() const
{
	return _size;
}

template<typename T>
size_t MyVector<T>::capacity() const
{
	return _capacity;
}

template<typename T>
T& MyVector<T>::at(int index)
{
	if (index < 0 || index >= _size)
	{
		throw std::out_of_range("Index is out of range!");
	}
	return _data[index];
}

template<typename T>
const T& MyVector<T>::at(int index) const
{
	if (index < 0 || index >= _size)
	{
		throw std::out_of_range("Index is out of range!");
	}
	return _data[index];
}

template<typename T>
T& MyVector<T>::operator[](int index)
{
	return _data[index];
}

template<typename T>
const T& MyVector<T>::operator[](int index) const
{
	return _data[index];
}

template<typename T>
T& MyVector<T>::front()
{
	if (empty())
	{
		throw std::logic_error("Vector is empty!");
	}
	return _data[0];
}

template<typename T>
T MyVector<T>::front_or_default() const
{
	return empty() ? T() : _data[0];
}

template<typename T>
const T& MyVector<T>::front() const
{
	if (empty())
	{
		throw std::logic_error("Vector is empty!");
	}
	return _data[0];
}

template<typename T>
T MyVector<T>::back_or_default() const
{
	return empty() ? T() : _data[_size - 1];
}

template<typename T>
T& MyVector<T>::back()
{
	if (empty())
	{
		throw std::logic_error("Vector is empty!");
	}
	return _data[_size - 1];
}

template<typename T>
const T& MyVector<T>::back() const
{
	if (empty())
	{
		throw std::logic_error("Vector is empty!");
	}
	return _data[_size - 1];
}

template<typename T>
bool MyVector<T>::contains(const T& element) const
{
	return indexOf(element) != -1;
}

template<typename T>
bool MyVector<T>::any(std::function<bool(const T&)> pred) const
{
	return indexOf(pred) != -1;
}

template <typename T>
MyVector<T> MyVector<T>::filter(std::function<bool(const T&)> pred) const
{
	MyVector<T> result;
	for (size_t i = 0; i < _size; i++)
	{
		if (pred(_data[i]))
		{
			result.push_back(_data[i]);
		}
	}
	return result;
}

template<typename T>
int MyVector<T>::indexOf(const T& element) const
{
	for (size_t i = 0; i < _size; i++)
	{
		if (element == _data[i])
		{
			return i;
		}
	}
	return -1;
}

template <typename T>
int MyVector<T>::indexOf(std::function<bool(const T&)> pred) const
{
	for (size_t i = 0; i < _size; i++)
	{
		if (pred(_data[i]))
		{
			return i;
		}
	}
	return -1;
}

template<typename T>
size_t MyVector<T>::count(std::function<bool(const T&)> pred) const
{
	size_t count = 0;
	for (size_t i = 0; i < _size; i++)
	{
		if (pred(_data[i]))
		{
			count++;
		}
	}
	return count;
}

template<typename T>
bool MyVector<T>::empty() const
{
	return _size == 0;
}

template<typename T>
void MyVector<T>::shrink_to_fit()
{
	resize(_size);
}

template<typename T>
void MyVector<T>::clear()
{
	shiftLeft(0, _size);
}

template<typename T>
void MyVector<T>::insert(int index, const T& element)
{
	if (index < 0)
	{
		throw std::out_of_range("Index cannot be negative!");
	}
	if (index >= _size)
	{
		push_back(element);
		return;
	}
	shiftRight(index, 1);
	_data[index] = element;
}

template<typename T>
void MyVector<T>::insert(int index, T&& element)
{
	if (index < 0)
	{
		throw std::out_of_range("Index cannot be negative!");
	}
	if (index >= _size)
	{
		push_back(std::move(element));
		return;
	}
	shiftRight(index, 1);
	_data[index] = std::move(element);
}

template<typename T>
void MyVector<T>::insert_range(int index, const MyVector& vector)
{
	if (index < 0)
	{
		throw std::out_of_range("Index cannot be negative!");
	}
	if (index >= _size)
	{
		append_range(vector);
		return;
	}
	shiftRight(index, vector._size);
	for (size_t i = 0; i < vector._size; i++)
	{
		_data[i + index] = vector._data[i];
	}
}

template<typename T>
void MyVector<T>::insert_range(int index, MyVector&& vector)
{
	if (index < 0)
	{
		throw std::out_of_range("Index cannot be negative!");
	}
	if (index >= _size)
	{
		append_range(std::move(vector));
		return;
	}
	shiftRight(index, vector._size);

	for (size_t i = 0; i < vector._size; i++)
	{
		_data[i + index] = std::move(vector._data[i]);
	}
}

template<typename T>
void MyVector<T>::erase(int index)
{
	erase(index, index);
}

template<typename T>
void MyVector<T>::erase(int start, int end)
{
	if (start < 0 || end < 0 || start >= _size || start > end)
	{
		throw std::out_of_range("Index is out of range!");
	}
	if (end >= _size)
	{
		end = _size - 1;
	}
	shiftLeft(start, end - start + 1);
}

template<typename T>
bool MyVector<T>::erase(std::function<bool(const T&)> pred)
{
	bool deleted = false;
	for (size_t i = 0; i < _size; i++)
	{
		if (pred(_data[i]))
		{
			erase(i);
			deleted = true;
		}
	}
	return deleted;
}

template<typename T>
void MyVector<T>::push_back(const T& element)
{
	shiftRight(_size, 1);
	_data[_size - 1] = element;
}

template<typename T>
void MyVector<T>::push_back(T&& element)
{
	shiftRight(_size, 1);
	_data[_size - 1] = std::move(element);
}

template<typename T>
void MyVector<T>::append(const T& element, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		push_back(element);
	}
}

template<typename T>
void MyVector<T>::append(T&& element, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		push_back(std::move(element));
	}
}

template<typename T>
void MyVector<T>::append_range(const MyVector& vector)
{
	shiftRight(_size, vector._size);
	for (size_t i = 0; i < vector._size; i++)
	{
		_data[_size - vector._size + i] = vector._data[i];
	}
}

template<typename T>
void MyVector<T>::append_range(MyVector&& vector)
{
	shiftRight(_size, vector._size);
	for (size_t i = 0; i < vector._size; i++)
	{
		_data[_size - vector._size + i] = std::move(vector._data[i]);
	}
}

template<typename T>
void MyVector<T>::pop_back()
{
	if (empty())
	{
		throw std::logic_error("Vector is empty!");
	}
	shiftLeft(_size, 1);
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& vector)
{
	for (size_t i = 0; i < vector.size(); i++)
	{
		os << vector[i] << " ";
	}
	return os;
}

template<typename T>
bool operator==(const MyVector<T>& lhs, const MyVector<T>& rhs)
{
	if (lhs.size() != rhs.size())
	{
		return false;
	}

	for (size_t i = 0; i < lhs.size(); i++)
	{
		if (lhs[i] != rhs[i])
		{
			return false;
		}
	}
	return true;
}

template<typename T>
bool operator!=(const MyVector<T>& lhs, const MyVector<T>& rhs)
{
	return !(lhs == rhs);
}

template<typename T>
bool operator<(const MyVector<T>& lhs, const MyVector<T>& rhs)
{
	for (size_t i = 0; i < std::min(lhs.size(), rhs.size()); i++)
	{
		if (lhs[i] >= rhs[i])
		{
			return false;
		}
	}
	return true;
}

template<typename T>
bool operator<=(const MyVector<T>& lhs, const MyVector<T>& rhs)
{
	return !(rhs < lhs);
}

template<typename T>
bool operator>(const MyVector<T>& lhs, const MyVector<T>& rhs)
{
	return !(lhs <= rhs);
}

template<typename T>
bool operator>=(const MyVector<T>& lhs, const MyVector<T>& rhs)
{
	return !(lhs < rhs);
}

template<typename T>
template<typename _Out>
MyVector<_Out> MyVector<T>::convertTo(std::function<_Out(const T&)> selector) const
{
	MyVector<_Out> result;
	for (size_t i = 0; i < _size; i++)
	{
		result.push_back(selector(_data[i]));
	}
	return result;
}
