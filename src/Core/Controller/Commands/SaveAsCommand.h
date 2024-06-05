#pragma once
#include "ControllerCommand.h"
class SaveAsCommand : public ControllerCommand
{
public:
	SaveAsCommand(XMLController& controller, const MyVector<MyString>& arguments);
	virtual void execute() const override;
	virtual ControllerCommand* clone() const override;
};