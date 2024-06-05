#pragma once
#include "ControllerCommand.h"
class XPathCommand : public ControllerCommand
{
public:
	XPathCommand(XMLController& controller, const MyVector<MyString>& arguments);
	virtual void execute() const override;
	virtual ControllerCommand* clone() const override;
};