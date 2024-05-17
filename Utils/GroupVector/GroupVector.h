#pragma once
#include "../MyVector/MyVector.hpp"
#include "../MyString/MyString.h"
struct Grouping
{
	MyString id;
	int occs = 0;
};
class GroupVector : public MyVector<Grouping>
{
public:
	void add(const MyString& id);
	int operator[](const MyString& id) const;
	int& operator[](const MyString& id);
};