#pragma once
#include "Counter.h"

template <typename T>
class ControlBlock
{
	T* _ptr = nullptr;
	Counter* _refCounter = nullptr;
public:
	ControlBlock(T* ptr);
	~ControlBlock();
	void addReference();
	int release();
	T* getPtr() const;
	int getRefCount() const;
};

template<typename T>
ControlBlock<T>::ControlBlock(T* ptr) : _ptr(ptr), _refCounter(new Counter())
{
	_refCounter->addPointer();
}

template<typename T>
ControlBlock<T>::~ControlBlock()
{
	delete _ptr;
	_ptr = nullptr;
	delete _refCounter;
	_refCounter = nullptr;
}

template<typename T>
void ControlBlock<T>::addReference()
{
	_refCounter->addPointer();
}

template<typename T>
int ControlBlock<T>::release()
{
	_refCounter->removePointer();
	return _refCounter->getCount();
}

template<typename T>
T* ControlBlock<T>::getPtr() const
{
	return _ptr;
}

template<typename T>
int ControlBlock<T>::getRefCount() const
{
	return _refCounter->getCount();
}
