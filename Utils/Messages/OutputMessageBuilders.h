#pragma once
#include "..\MyString\MyString.h"
struct OutputMessageBuilders
{
	static MyString SUCCESSFULLY_OPENED_FILE(const MyString& filename)
	{
		return "Successfully opened " + filename;
	}
	static MyString FILE_ALREADY_OPENED(const MyString& opened, const MyString& attempted)
	{
		return "A file (" + opened + ") is still opened! Close it in order to open " + attempted;
	}
	static MyString FILE_NOT_OPENED(const MyString& filename)
	{
		return "File " + filename + " is not opened, therefore you can't close it";
	}
	static MyString SUCCESSFULLY_CLOSED_FILE(const MyString& filename)
	{
		return "Successfully closed " + filename;
	}
	static MyString NO_FILE_OPENED_FOR_SAVING()
	{
		return "No files are opened for saving";
	}
	static MyString SUCCESSFULLY_SAVED_FILE(const MyString& filename)
	{
		return "Successfully saved " + filename;
	}
};