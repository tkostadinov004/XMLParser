#pragma once
#include "ControllerCommand.h"
class TextCommand : public ControllerCommand
{
public:
	TextCommand(XMLController& controller, const MyVector<MyString>& arguments);
	virtual void execute() const override;
	virtual ControllerCommand* clone() const override;
};