#pragma once
#include <iostream>
template <typename T>
class PointerWrapper
{
	T* _ptr = nullptr;
	void copyFrom(const PointerWrapper& other);
	void moveFrom(PointerWrapper&& other);
	void free();
public:
	PointerWrapper(T* ptr = nullptr);
	PointerWrapper(const PointerWrapper& other);
	PointerWrapper& operator=(const PointerWrapper& other);
	PointerWrapper(PointerWrapper&& other) noexcept;
	PointerWrapper& operator=(PointerWrapper&& other) noexcept;
	~PointerWrapper();
	T& operator*();
	const T& operator*() const;
	T* operator->();
	const T* operator->() const;
	const T* get() const;
	T*& get();
};

template<typename T>
void PointerWrapper<T>::copyFrom(const PointerWrapper& other)
{
	_ptr = other._ptr ? other._ptr->clone() : nullptr;
}

template<typename T>
void PointerWrapper<T>::moveFrom(PointerWrapper&& other)
{
	this->_ptr = other._ptr;
	other._ptr = nullptr;
}

template<typename T>
void PointerWrapper<T>::free()
{
	delete _ptr;
	_ptr = nullptr;
}

template<typename T>
PointerWrapper<T>::PointerWrapper(T* ptr) : _ptr(ptr)
{
}

template<typename T>
PointerWrapper<T>::PointerWrapper(const PointerWrapper& other)
{
	copyFrom(other);
}

template<typename T>
PointerWrapper<T>& PointerWrapper<T>::operator=(const PointerWrapper& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
PointerWrapper<T>::PointerWrapper(PointerWrapper&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
PointerWrapper<T>& PointerWrapper<T>::operator=(PointerWrapper&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
PointerWrapper<T>::~PointerWrapper()
{
	free();
}

template<typename T>
T& PointerWrapper<T>::operator*()
{
	return *_ptr;
}

template<typename T>
const T& PointerWrapper<T>::operator*() const
{
	return *_ptr;
}

template<typename T>
T* PointerWrapper<T>::operator->()
{
	return _ptr;
}

template<typename T>
const T* PointerWrapper<T>::operator->() const
{
	return _ptr;
}

template<typename T>
const T* PointerWrapper<T>::get() const
{
	return _ptr;
}
template<typename T>
T*& PointerWrapper<T>::get()
{
	return _ptr;
}
