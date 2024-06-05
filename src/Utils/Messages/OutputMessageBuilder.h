#pragma once
#include "..\MyString\MyString.h"
struct OutputMessageBuilder
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
	static MyString SUCCESSFULLY_SAVED_FILE(const MyString& filename)
	{
		return "Successfully saved " + filename;
	}
	static MyString SUCCESSFULLY_CHANGED_ATTRIBUTE(const MyString& attributeName, const MyString& newValue)
	{
		return "Successfully changed the value of " + attributeName + " to " + newValue;
	}
	static MyString SUCCESSFULLY_DELETED_ATTRIBUTE(const MyString& attributeName, const MyString& nodeId)
	{
		return "Successfully deleted attribute with name \"" + attributeName + "\" from node with id \"" + nodeId + "\"";
	}
	static MyString SUCCESSFULLY_ADDED_CHILD(const MyString& newChildName, const MyString& nodeId)
	{
		return "Successfully added child with name \"" + newChildName + "\" to node with id \"" + nodeId + "\"";
	}
};