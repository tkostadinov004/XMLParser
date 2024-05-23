#pragma once
#include <iostream>
#include "Counter.h"
template <typename T>
class MySharedPtr
{
	template <typename T> friend class MyWeakPtr;

	T* _ptr = nullptr;
	Counter* _refCounter = nullptr;
	void copyFrom(const MySharedPtr& other);
	void free();
public:
	MySharedPtr(T* ptr = nullptr);
	~MySharedPtr();
	MySharedPtr(const MySharedPtr& other);
	MySharedPtr& operator=(const MySharedPtr& other);
	T* get() const;
	T& operator*() const;
	T* operator->() const;
	int use_count() const;
	operator bool() const;

	template <typename U>
	MySharedPtr(const MySharedPtr<U>& other);

	template<typename U> friend class MySharedPtr;
};

template<typename T>
void MySharedPtr<T>::copyFrom(const MySharedPtr& other)
{
	_ptr = other._ptr;
	_refCounter = other._refCounter;
	if (_refCounter)
	{
		_refCounter->addSharedPointer();
	}
}

template<typename T>
void MySharedPtr<T>::free()
{
	if (!_ptr && !_refCounter)
	{
		return;
	}

	_refCounter->removeSharedPointer();
	if (_refCounter->getSharedCount() == 0)
	{
		delete _ptr;
	}
	if (_refCounter->getWeakCount() == 0)
	{
		delete _refCounter;
	}
}

template<typename T>
MySharedPtr<T>::MySharedPtr(T* ptr) : _ptr(ptr)
{
	if (_ptr)
	{
		_refCounter = new Counter();
		_refCounter->addSharedPointer();
	}
}

template<typename T>
MySharedPtr<T>::~MySharedPtr()
{
	free();
}

template<typename T>
MySharedPtr<T>::MySharedPtr(const MySharedPtr& other)
{
	copyFrom(other);
}

template<typename T>
template<typename U>
MySharedPtr<T>::MySharedPtr(const MySharedPtr<U>& other)
{
	_ptr = reinterpret_cast<T*>(other._ptr);
	_refCounter = other._refCounter;
	if (_refCounter)
	{
		_refCounter->addSharedPointer();
	}
}

template<typename T>
MySharedPtr<T>& MySharedPtr<T>::operator=(const MySharedPtr& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
T* MySharedPtr<T>::get() const
{
	return _ptr;
}

template<typename T>
T& MySharedPtr<T>::operator*() const
{
	return *get();
}

template<typename T>
T* MySharedPtr<T>::operator->() const
{
	return get();
}

template<typename T>
int MySharedPtr<T>::use_count() const
{
	return _refCounter->getSharedCount();
}
template<typename T>
MySharedPtr<T>::operator bool() const
{
	return _ptr != nullptr;
}
