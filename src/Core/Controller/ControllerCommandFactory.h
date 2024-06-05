#pragma once
#include "Commands\ControllerCommand.h"
class ControllerCommandFactory
{
public:
	MySharedPtr<ControllerCommand> create(XMLController& controller, const MyString& commandName, const MyVector<MyString>& arguments) const;
};