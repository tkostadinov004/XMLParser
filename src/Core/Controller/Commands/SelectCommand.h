#pragma once
#include "ControllerCommand.h"
class SelectCommand : public ControllerCommand
{
public:
	SelectCommand(XMLController& controller, const MyVector<MyString>& arguments);
	virtual void execute() const override;
	virtual ControllerCommand* clone() const override;
};