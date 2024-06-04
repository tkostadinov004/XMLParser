#pragma once

template <typename T>
class VectorIterator
{
	T* _ptr;
	size_t _index = 0;
public:
	explicit VectorIterator(T* ptr, size_t index);
	T& operator*() const;
	VectorIterator& operator++();
	bool operator!=(const VectorIterator& other) const;
};

template <typename T>
VectorIterator<T>::VectorIterator(T* ptr, size_t index) : _ptr(ptr), _index(index) {}

template<typename T>
T& VectorIterator<T>::operator*() const
{
	return *(_ptr + _index);
}

template<typename T>
typename VectorIterator<T>& VectorIterator<T>::operator++()
{
	_index++;
	return *this;
}

template<typename T>
bool VectorIterator<T>::operator!=(const VectorIterator<T>& other) const
{
	return _index != other._index;
}