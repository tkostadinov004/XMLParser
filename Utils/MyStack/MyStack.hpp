#pragma once
#include "../MyVector/MyVector.hpp"

template <typename T>
class MyStack : private MyVector<T>
{
public:
	using MyVector<T>::size;
	using MyVector<T>::empty;
	using MyVector<T>::convertTo;
	void push(const T& element);
	const T& pop();
	const T& peek() const;
};

template<typename T>
void MyStack<T>::push(const T& element)
{
	MyVector<T>::push_back(element);
}

template<typename T>
const T& MyStack<T>::pop()
{
	T popped = MyVector<T>::back();
	MyVector<T>::pop_back();
	return popped;
}

template<typename T>
const T& MyStack<T>::peek() const
{
	return MyVector<T>::back();
}
