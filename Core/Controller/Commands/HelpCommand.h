#pragma once
#include "ControllerCommand.h"
class HelpCommand : public ControllerCommand
{
public:
	HelpCommand(XMLController& controller, const MyVector<MyString>& arguments);
	virtual void execute() const override;
	virtual ControllerCommand* clone() const override;
};