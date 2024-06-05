#pragma once
#include "..\XMLController.h"
#include "..\..\..\Utils\MyString\MyString.h"
class ControllerCommand
{
protected:
	XMLController& _controller;
	MyString _name;
	size_t _argumentsNeeded = 0;
	MyVector<MyString> _arguments;
public:
	ControllerCommand(XMLController& controller, const MyString& name, const MyVector<MyString>& arguments, size_t argumentsNeeded);
	virtual void execute() const = 0;
	virtual ControllerCommand* clone() const = 0;

	void setArguments(const MyVector<MyString>& arguments, size_t argumentsNeeded);
};