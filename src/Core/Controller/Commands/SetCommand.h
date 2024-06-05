#pragma once
#include "ControllerCommand.h"
class SetCommand : public ControllerCommand
{
public:
	SetCommand(XMLController& controller, const MyVector<MyString>& arguments);
	virtual void execute() const override;
	virtual ControllerCommand* clone() const override;
};