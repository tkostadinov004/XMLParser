#pragma once
#include "../MySharedPtr/MySharedPtr.hpp"
#include "..\MySharedPtr\Counter.h"

template <typename T>
class MyWeakPtr
{
	T* _ptr = nullptr;
	Counter* _refCounter = nullptr;
	void copyFrom(const MyWeakPtr& other);
	void moveFrom(MyWeakPtr&& other);
	void free();
public:
	MyWeakPtr() = default;
	MyWeakPtr(T* ptr);
	MyWeakPtr(MySharedPtr<T>& ptr);
	MyWeakPtr(const MyWeakPtr<T>& other);
	MyWeakPtr(MyWeakPtr<T>&& other);
	MyWeakPtr& operator=(const MyWeakPtr<T>& other);
	MyWeakPtr& operator=(MyWeakPtr<T>&& other);
	~MyWeakPtr();
	T* get() const;
	T& operator*() const;
	T* operator->() const;
	operator bool() const;

	template <typename U>
	MyWeakPtr(const MyWeakPtr<U>& other);
	template<typename U> friend class MyWeakPtr;
};

template<typename T>
void MyWeakPtr<T>::copyFrom(const MyWeakPtr& other)
{
	_ptr = other._ptr;
	_refCounter = other._refCounter;
	if (_refCounter)
	{
		_refCounter->addWeakPointer();
	}
}

template<typename T>
void MyWeakPtr<T>::moveFrom(MyWeakPtr&& other)
{
	_ptr = other._ptr;
	other._ptr = nullptr;
	_refCounter = other._refCounter;
	other._refCounter = nullptr;
}

template<typename T>
void MyWeakPtr<T>::free()
{
	if (!_refCounter)
	{
		return;
	}

	_refCounter->removeWeakPointer();
	if (_refCounter->getWeakCount() == 0)
	{
		delete _refCounter;
		_refCounter = nullptr;
	}
}

template<typename T>
MyWeakPtr<T>::MyWeakPtr(T* ptr) : _ptr(ptr)
{
	if (_ptr)
	{
		_refCounter = new Counter();
		_refCounter->addWeakPointer();
	}
}

template<typename T>
MyWeakPtr<T>::MyWeakPtr(MySharedPtr<T>& ptr)
{
	_ptr = ptr._ptr;
	_refCounter = ptr._refCounter;
	if (_refCounter)
	{
		_refCounter->addWeakPointer();
	}
}

template<typename T>
MyWeakPtr<T>::MyWeakPtr(const MyWeakPtr<T>& other)
{
	copyFrom(other);
}

template<typename T>
MyWeakPtr<T>::MyWeakPtr(MyWeakPtr<T>&& other)
{
	moveFrom(std::move(other));
}

template<typename T>
MyWeakPtr<T>& MyWeakPtr<T>::operator=(const MyWeakPtr<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
MyWeakPtr<T>& MyWeakPtr<T>::operator=(MyWeakPtr<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
MyWeakPtr<T>::~MyWeakPtr()
{
	free();
}

template<typename T>
T* MyWeakPtr<T>::get() const
{
	return _ptr;
}

template<typename T>
T& MyWeakPtr<T>::operator*() const
{
	return *get();
}

template<typename T>
T* MyWeakPtr<T>::operator->() const
{
	return get();
}

template<typename T>
MyWeakPtr<T>::operator bool() const
{
	return _refCounter && _refCounter->getSharedCount() == 0;
}

template<typename T>
template<typename U>
MyWeakPtr<T>::MyWeakPtr(const MyWeakPtr<U>& other)
{
	_ptr = reinterpret_cast<T*>(other._ptr);
	_refCounter = other._refCounter;
	if (_refCounter)
	{
		_refCounter->addWeakPointer();
	}
}