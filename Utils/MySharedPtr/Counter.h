#pragma once
class Counter
{
	unsigned _useCount = 0;
	//unsigned _weakCount = 0;
public:
	Counter() = default;
	Counter(Counter&&) = delete;
	Counter& operator=(Counter&&) = delete;
	void reset();
	unsigned getCount() const;
	void addPointer();
	void removePointer();
};