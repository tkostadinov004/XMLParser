#include "OpenCommand.h"

OpenCommand::OpenCommand(XMLController& controller, const MyVector<MyString>& arguments) : ControllerCommand(controller, "open", arguments, 1)
{
}

void OpenCommand::execute() const
{
	const MyString& path = _arguments[0];
	_controller.openFile(path);
}

ControllerCommand* OpenCommand::clone() const
{
	return new OpenCommand(*this);
}