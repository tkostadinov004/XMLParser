#pragma once
class Counter
{
	unsigned _useCount = 0;
	unsigned _weakCount = 0;
public:
	Counter() = default;
	Counter(Counter&&) = delete;
	Counter& operator=(Counter&&) = delete;
	void reset();
	unsigned getSharedCount() const;
	unsigned getWeakCount() const;
	void addSharedPointer();
	void addWeakPointer();
	void removeSharedPointer();
	void removeWeakPointer();
};