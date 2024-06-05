#pragma once
#include "ControllerCommand.h"
class ChildrenCommand : public ControllerCommand
{
public:
	ChildrenCommand(XMLController& controller, const MyVector<MyString>& arguments);
	virtual void execute() const override;
	virtual ControllerCommand* clone() const override;
};