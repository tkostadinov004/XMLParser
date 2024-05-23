#include "Counter.h"

void Counter::reset()
{
    _useCount = 0;
}

unsigned Counter::getCount() const
{
    return _useCount;
}

void Counter::addPointer()
{
    _useCount++;
}

void Counter::removePointer()
{
    _useCount--;
}