#pragma once
#include "../../../Utils/MyVector/MyVector.hpp"

template <typename T>
class Repository
{
public:
	virtual void add(const T& item) = 0;
	virtual bool remove(const T& item) = 0;
};