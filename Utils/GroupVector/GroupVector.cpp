#include "GroupVector.h"

void GroupVector::add(const MyString& id)
{
	int index = indexOf([id](const Grouping& group) {return group.id == id;});
	if (index == -1)
	{
		Grouping newGroup = { id, 1 };
		push_back(newGroup);
	}
	else
	{
		_data[index].occs++;
	}
}

int GroupVector::operator[](const MyString& id) const
{
	int index = indexOf([id](const Grouping& group) {return group.id == id;});
    return _data[index].occs;
}

int& GroupVector::operator[](const MyString& id)
{
	int index = indexOf([id](const Grouping& group) {return group.id == id;});
	return _data[index].occs;
}

bool GroupVector::contains(const MyString& id) const
{
	return indexOf([id](const Grouping& group) {return group.id == id;}) != -1;
}
