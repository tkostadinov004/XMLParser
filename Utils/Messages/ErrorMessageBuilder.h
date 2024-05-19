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
	static MyString UNABLE_TO_FIND_NODE(const MyString& nodeId)
	{
		return "Unable to find node with id \"" + nodeId + "\"";
	}
	static MyString UNABLE_TO_FIND_ATTRIBUTE_IN_NODE(const MyString& attributeName, const MyString& nodeId)
	{
		return "Unable to find attribite with key \"" + attributeName + "\" in a node with id \"" + nodeId + "\"";
	}
};