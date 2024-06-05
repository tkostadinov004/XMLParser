#pragma once
#include "ControllerCommand.h"
class PrintCommand : public ControllerCommand
{
public:
	PrintCommand(XMLController& controller, const MyVector<MyString>& arguments);
	virtual void execute() const override;
	virtual ControllerCommand* clone() const override;
};