#include "DeleteCommand.h"

DeleteCommand::DeleteCommand(XMLController& controller, const MyVector<MyString>& arguments) : ControllerCommand(controller, "delete", arguments, 2)
{
}

void DeleteCommand::execute() const
{
    const MyString& nodeId = _arguments[0];
    const MyString& attributeName = _arguments[1];

    _controller.deleteAttribute(nodeId, attributeName);
}

ControllerCommand* DeleteCommand::clone() const
{
    return new DeleteCommand(*this);
}