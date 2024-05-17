#pragma once
#include "XML/Repositories/XMLRepository.h"
#include "../Utils/Messages/ErrorMessages.h"
#include "../Utils/Messages/OutputMessageBuilders.h"

class XMLController
{
	XMLRepository _repository;
	MyString _currentFilePath;
	MyString _currentFileName;
public:
	MyString openFile(const MyString& path);
	MyString closeFile();
	MyString save();
	MyString saveAs(const MyString& path);
	MyString help();
};