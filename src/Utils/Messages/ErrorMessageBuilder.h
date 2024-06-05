#pragma once
#include "..\MyString\MyString.h"
struct ErrorMessageBuilder
{
	static MyString ERROR_OPENING_FILE(const MyString& filename)
	{
		return "Unable to open " + filename;
	}
	static MyString ERROR_SAVING_TO_FILE(const MyString& filename)
	{
		return "Unable to save to " + filename;
	}
	static MyString UNABLE_TO_OPEN_OR_CREATE_FILE()
	{
		return "Unable to open or create file!";
	}
	static MyString NO_FILE_OPENED_FOR_SAVING()
	{
		return "No files are opened for saving";
	}
	static MyString NO_FILE_OPENED()
	{
		return "No files are opened";
	}
	static MyString UNABLE_TO_FIND_NODE(const MyString& nodeId)
	{
		return "Unable to find node with id \"" + nodeId + "\"";
	}
	static MyString UNABLE_TO_FIND_ATTRIBUTE_IN_NODE(const MyString& attributeName, const MyString& nodeId)
	{
		return "Unable to find attribite with key \"" + attributeName + "\" in a node with id \"" + nodeId + "\"";
	}
	static MyString INSUFFICIENT_ARGUMENTS_FOR(const MyString& commandName)
	{
		return "Insufficient arguments for \"" + commandName + "\"!";
	}
	static MyString ATTRIBUTE_NOT_FOUND(const MyString& attributeName, const MyString& nodeId)
	{
		return "Attribute with name \"" + attributeName + "\" is not found in the node with id \"" + nodeId + "\"";
	}
	static const char* INVALID_INDEX()
	{
		return "Index is out of bounds!";
	}
	static const char* ATTRIBUTE_NAME_EMPTY()
	{
		return "Attribute name cannot be empty!";
	}
	static const char* INVALID_COMMAND_NAME()
	{
		return "Invalid command name!";
	}
};