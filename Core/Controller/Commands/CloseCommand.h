#pragma once
#include "ControllerCommand.h"
class CloseCommand : public ControllerCommand
{
public:
	CloseCommand(XMLController& controller, const MyVector<MyString>& arguments);
	virtual void execute() const override;
	virtual ControllerCommand* clone() const override;
};