#include "SetCommand.h"

SetCommand::SetCommand(XMLController& controller, const MyVector<MyString>& arguments) : ControllerCommand(controller, "set", arguments, 3)
{
}

void SetCommand::execute() const
{
	const MyString& nodeId = _arguments[0];
	const MyString& attributeName = _arguments[1];
	const MyString& newValue = _arguments[2];

	_controller.changeAttributeValue(nodeId, attributeName, newValue);
}

ControllerCommand* SetCommand::clone() const
{
    return new SetCommand(*this);
}
