#pragma once
#include "../DataReader.h"
#include "../../../../../../Utils/MyWeakPtr/MyWeakPtr.hpp"
#include "../../../../Models/XMLElementNode.h"
template <typename T>
class XMLBuilder
{
protected:
	DataReader& _reader;
public:
	explicit XMLBuilder(DataReader& reader);
	virtual MySharedPtr<T> flush(MyWeakPtr<XMLElementNode> parent) = 0;
};

template<typename T>
XMLBuilder<T>::XMLBuilder(DataReader& reader) : _reader(reader)
{
}
