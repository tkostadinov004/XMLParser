#pragma once
#include "ControllerCommand.h"
class SaveCommand : public ControllerCommand
{
public:
	SaveCommand(XMLController& controller, const MyVector<MyString>& arguments);
	virtual void execute() const override;
	virtual ControllerCommand* clone() const override;
};