#include "SelectCommand.h"

SelectCommand::SelectCommand(XMLController& controller, const MyVector<MyString>& arguments) : ControllerCommand(controller, "select", arguments, 2)
{
}

void SelectCommand::execute() const
{
    const MyString& nodeId = _arguments[0];
    const MyString& attributeName = _arguments[1];

    _controller.selectAttribute(nodeId, attributeName);
}

ControllerCommand* SelectCommand::clone() const
{
    return new SelectCommand(*this);
}
