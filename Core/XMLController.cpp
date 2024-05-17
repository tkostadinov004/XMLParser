#include "XMLController.h"

MyString XMLController::openFile(const MyString& path)
{
	if (!_currentFileName.empty())
	{
		return OutputMessageBuilders::FILE_ALREADY_OPENED(_currentFileName, path.split('\\').back_or_default());
	}

	_repository.open(path);
	_currentFilePath = path;
	_currentFileName = path.split('\\').back_or_default();
	return OutputMessageBuilders::SUCCESSFULLY_OPENED_FILE(path);
}

MyString XMLController::closeFile()
{
	if (_currentFilePath.empty())
	{
		return OutputMessageBuilders::FILE_NOT_OPENED(_currentFileName);
	}

	_repository.close();
	_currentFilePath.clear();
	_currentFileName.clear();
	return OutputMessageBuilders::SUCCESSFULLY_CLOSED_FILE(_currentFileName);
}

MyString XMLController::save()
{
	if (_currentFilePath.empty())
	{
		return OutputMessageBuilders::NO_FILE_OPENED_FOR_SAVING();
	}
	_repository.saveAs(_currentFilePath);

	return OutputMessageBuilders::SUCCESSFULLY_SAVED_FILE(_currentFileName);
}

MyString XMLController::saveAs(const MyString& path)
{
	_repository.saveAs(path);

	return OutputMessageBuilders::SUCCESSFULLY_SAVED_FILE(path.split('\\').back_or_default());
}

MyString XMLController::help()
{
	MyString result;
	result += "The following commands are supported:\nopen <file>\t\topens <file>\nclose\t\tcloses currently opened file\nsave\t\tsaves the currently open file\nsaveas <file>\t\tsaves the currently open file in <file>\nhelp\t\tprints this information\nexit\t\texists the program";
	return result;
}
