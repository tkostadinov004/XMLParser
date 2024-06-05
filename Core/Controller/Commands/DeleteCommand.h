#pragma once
#include "ControllerCommand.h"
class DeleteCommand : public ControllerCommand
{
public:
	DeleteCommand(XMLController& controller, const MyVector<MyString>& arguments);
	virtual void execute() const override;
	virtual ControllerCommand* clone() const override;
};