#include "NewChildCommand.h"

NewChildCommand::NewChildCommand(XMLController& controller, const MyVector<MyString>& arguments) : ControllerCommand(controller, "newchild", arguments, 1)
{
}

void NewChildCommand::execute() const
{
    const MyString& nodeId = _arguments[0];

    _controller.addChild(nodeId);
}

ControllerCommand* NewChildCommand::clone() const
{
    return new NewChildCommand(*this);
}