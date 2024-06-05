#include "Reader.h"

MyVector<MyString> Reader::splitAndIgnore(const MyString& str, char delim, bool removeEmptyEntries) const
{
	MyVector<MyString> splitted;
	bool isInQuotes = false;

	MyString temp;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == delim && !isInQuotes)
		{
			if (removeEmptyEntries && temp.empty())
			{
				continue;
			}
			splitted.push_back(temp);
			temp.clear();
		}
		else if (str[i] == '\"')
		{
			isInQuotes = !isInQuotes;
		}
		else
		{
			temp.append(str[i]);
		}
	}
	splitted.push_back(temp);
	return splitted;
}