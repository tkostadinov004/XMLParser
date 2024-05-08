#pragma once

#include <fstream>
#include "..\Utils\MyString\MyString.h"

class FileManager
{
	MyString _filepath;
	std::fstream _stream;
public:
	void open(const MyString& path, std::ios_base::open_mode open_mode);
	void close();

	template <typename T>
	void save(const T& obj) const;

	template <typename T>
	void saveAs(const T& obj, const MyString& path) const;

	bool isOpen() const;
};

#include "..\Utils\Exceptions\FileError.h"
#include "..\Utils\ErrorMessages.h"

inline void FileManager::open(const MyString& path, std::ios_base::open_mode open_mode)
{
	_stream.close();
	_stream.open(path.c_str(), open_mode);
	if (!_stream.is_open())
	{
		throw FileError(ErrorMessages::ERROR_OPENING_FILE);
	}
	_filepath = path;
}

void FileManager::close()
{
	_stream.close();
	_filepath.clear();
}

template<typename T>
void FileManager::save(const T& obj) const
{
	saveAs(obj, _filepath);
}

template<typename T>
void FileManager::saveAs(const T& obj, const MyString& path) const
{
	std::ofstream ofs(path.c_str());
	if (!ofs.is_open())
	{
		throw FileError(ErrorMessages::ERROR_SAVING_TO_FILE);
	}
	ofs << obj;
}

bool FileManager::isOpen() const
{
	return _stream.is_open();
}