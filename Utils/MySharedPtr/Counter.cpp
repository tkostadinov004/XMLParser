#include "Counter.h"

void Counter::reset()
{
    _useCount = 0;
}

unsigned Counter::getSharedCount() const
{
    return _useCount;
}

unsigned Counter::getWeakCount() const
{
    return _weakCount;
}

void Counter::addSharedPointer()
{
    if (++_useCount == 1)
    {
        _weakCount++;
    }
}

void Counter::addWeakPointer()
{
    _weakCount++;
}

void Counter::removeSharedPointer()
{
    if (--_useCount == 0)
    {
        _weakCount--;
    }
}

void Counter::removeWeakPointer()
{
    _weakCount--;
}
