#pragma once
#include "ControllerCommand.h"
class ChildCommand : public ControllerCommand
{
public:
	ChildCommand(XMLController& controller, const MyVector<MyString>& arguments);
	virtual void execute() const override;
	virtual ControllerCommand* clone() const override;
};