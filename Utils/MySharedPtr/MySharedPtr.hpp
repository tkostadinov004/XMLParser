#pragma once
#include <iostream>
#include "ControlBlock.hpp"
template <typename T>
class MySharedPtr
{
	ControlBlock<T>* _controlBlock;
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
	_controlBlock = other._controlBlock;
	if (_controlBlock)
	{
		_controlBlock->addReference();
	}
}

template<typename T>
void MySharedPtr<T>::free()
{
	if (_controlBlock && _controlBlock->release() == 0)
	{
		delete _controlBlock;
		_controlBlock = nullptr;
	}
}

template<typename T>
MySharedPtr<T>::MySharedPtr(T* ptr) : _controlBlock(ptr ? new ControlBlock<T>(ptr) : nullptr)
{}

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
	: _controlBlock(reinterpret_cast<ControlBlock<T>*>(other._controlBlock))
{
	if (_controlBlock)
	{
		_controlBlock->addReference();
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
	return _controlBlock ? _controlBlock->getPtr() : nullptr;
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
	return _controlBlock ? _controlBlock->getRefCount() : 0;
}

template<typename T>
MySharedPtr<T>::operator bool() const
{
	return _controlBlock != nullptr;
}
