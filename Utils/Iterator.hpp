#pragma once
template <typename T>
class Iterator
{
public:
	Iterator(size_t index, T* ptr);
	T& operator*() const;
	Iterator& operator++();
	bool operator!=(const Iterator& other) const;
private:
	size_t _index;
	T* _ptr;
};

template <typename T>
Iterator<T>::Iterator(size_t index, T* ptr) : _index(index), _ptr(ptr) {}

template<typename T>
T& Iterator<T>::operator*() const
{
	return *(_ptr + _index);
}

template<typename T>
typename Iterator<T>& Iterator<T>::operator++()
{
	_index++;
	return *this;
}

template<typename T>
bool Iterator<T>::operator!=(const Iterator<T>& other) const
{
	return _index != other._index;
}