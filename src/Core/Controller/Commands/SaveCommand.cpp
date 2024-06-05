#include "SaveCommand.h"

SaveCommand::SaveCommand(XMLController& controller, const MyVector<MyString>& arguments) : ControllerCommand(controller, "save", arguments, 0)
{
}

void SaveCommand::execute() const
{
	_controller.save();
}

ControllerCommand* SaveCommand::clone() const
{
	return new SaveCommand(*this);
}