#pragma once
#include "ControllerCommand.h"
class NewChildCommand : public ControllerCommand
{
public:
	NewChildCommand(XMLController& controller, const MyVector<MyString>& arguments);
	virtual void execute() const override;
	virtual ControllerCommand* clone() const override;
};