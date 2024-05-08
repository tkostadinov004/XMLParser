#include "StringVector.h"
#include "HelperFunctions.h"

void StringVector::resize(size_t newCapacity)
{
    MyString* temp = _data;
    _data = new MyString[newCapacity];
    for (size_t i = 0; i < _size; i++)
    {
        _data[i] = std::move(temp[i]);
    }
    delete[] temp;
    _capacity = newCapacity;
}

void StringVector::moveFrom(StringVector&& other)
{
    this->_data = other._data;
    other._data = nullptr;
    this->_size = other._size;
    this->_capacity = other._capacity;
    other._size = other._capacity = 0;
}

void StringVector::copyFrom(const StringVector& other)
{
    this->_size = other._size;
    this->_capacity = other._capacity;
    this->_data = new MyString[other._capacity];
    for (size_t i = 0; i < other._size; i++)
    {
        this->_data[i] = other._data[i];
    }
}

void StringVector::free()
{
    delete[] _data;
    _data = nullptr;
    _size = 0;
    _capacity = 1;
}

StringVector::StringVector() : StringVector(1)
{
}

StringVector::StringVector(size_t capacity)
{
    this->_capacity = HelperFunctions::getNextPowerOfTwo(capacity);
    _data = new MyString[this->_capacity];
}

StringVector::StringVector(const MyString* arr, size_t size)
{
    if (!arr)
    {
        throw std::invalid_argument("Invalid array!");
    }

    this->_capacity = HelperFunctions::getNextPowerOfTwo(size);
    this->_data = new MyString[this->_capacity];
    for (size_t i = 0; i < size; i++)
    {
        this->push_back(arr[i]);
    }
}

StringVector::StringVector(const StringVector& other)
{
    copyFrom(other);
}

StringVector::StringVector(StringVector&& other)
{
    moveFrom(std::move(other));
}

StringVector& StringVector::operator=(const StringVector& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

StringVector& StringVector::operator=(StringVector&& other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

StringVector::~StringVector()
{
    free();
}

void StringVector::push_back(const MyString& str)
{
    if (_size + 1 > _capacity)
    {
        resize(HelperFunctions::getNextPowerOfTwo(_size + 1));
    }
    _data[_size++] = str;
}

void StringVector::push_back(MyString&& str)
{
    if (_size + 1 > _capacity)
    {
        resize(HelperFunctions::getNextPowerOfTwo(_size + 1));
    }
    _data[_size++] = std::move(str);
}

void StringVector::pop_back()
{
    if (this->empty())
    {
        throw std::logic_error("Vector is empty!");
    }
    _size--;
}

void StringVector::insert(const MyString& str, int index)
{
    if (index < 0 || index >= _size)
    {
        throw std::range_error("Index is out of range!");
    }
    if (_size + 1 > _capacity)
    {
        resize(HelperFunctions::getNextPowerOfTwo(_size + 1));
    }
    for (int i = _size - 1; i >= index; i--)
    {
        _data[i + 1].swap(_data[i]);
    }
    _data[index] = str;
    _size++;
}

void StringVector::insert(MyString&& str, int index)
{
    if (index < 0 || index >= _size)
    {
        throw std::range_error("Index is out of range!");
    }
    if (_size + 1 > _capacity)
    {
        resize(HelperFunctions::getNextPowerOfTwo(_size + 1));
    }
    for (int i = _size - 1; i >= index; i--)
    {
        _data[i + 1].swap(_data[i]);
    }
    _data[index] = std::move(str);
    _size++;
}

void StringVector::erase(int index)
{
    if (index < 0 || index >= _size)
    {
        throw std::range_error("Index is out of range!");
    }
    for (size_t i = index; i < _size - 1; i++)
    {
        _data[i].swap(_data[i + 1]);
    }
    _size--;
}

MyString& StringVector::operator[](int index)
{
    return _data[index];
}

const MyString& StringVector::operator[](int index) const
{
    return _data[index];
}

MyString& StringVector::at(int index)
{
    if (index < 0 || index >= _size)
    {
        throw std::range_error("Index is out of range!");
    }
    return _data[index];
}

const MyString& StringVector::at(int index) const
{
    if (index < 0 || index >= _size)
    {
        throw std::range_error("Index is out of range!");
    }
    return _data[index];
}

bool StringVector::empty() const
{
    return _size == 0;
}

size_t StringVector::size() const
{
    return _size;
}

std::ostream& operator<<(std::ostream& os, const StringVector& vector)
{
    os << "[ ";
    for (size_t i = 0; i < vector.size(); i++)
    {
        os << vector[i] << ", ";
    }
    if (!vector.empty())
    {
        os << "\b\b ";
    }
    os << "]";
    return os;
}

std::istream& operator>>(std::istream& is, StringVector& vector)
{
    char buffer[2048];
    is.getline(buffer, 2048);
    vector = HelperFunctions::split(MyString(buffer));
    return is;
}
