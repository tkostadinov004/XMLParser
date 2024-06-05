#include "NewChildCommand.h"

NewChildCommand::NewChildCommand(XMLController& controller, const MyVector<MyString>& arguments) : ControllerCommand(controller, "newchild", arguments, 2)
{
}

void NewChildCommand::execute() const
{
    const MyString& nodeId = _arguments[0];
    const MyString& newChildName = _arguments[1];

    _controller.addChild(nodeId, newChildName);
}

ControllerCommand* NewChildCommand::clone() const
{
    return new NewChildCommand(*this);
}