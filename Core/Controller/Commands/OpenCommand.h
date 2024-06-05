#pragma once
#include "ControllerCommand.h"
class OpenCommand : public ControllerCommand
{
public:
	OpenCommand(XMLController& controller, const MyVector<MyString>& arguments);
	virtual void execute() const override;
	virtual ControllerCommand* clone() const override;
};