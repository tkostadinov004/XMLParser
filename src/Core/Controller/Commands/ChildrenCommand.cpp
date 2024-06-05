#include "ChildrenCommand.h"

ChildrenCommand::ChildrenCommand(XMLController& controller, const MyVector<MyString>& arguments) : ControllerCommand(controller,"children", arguments, 1)
{
}

void ChildrenCommand::execute() const
{
    const MyString& nodeId = _arguments[0];

    _controller.printChildrenOfNode(nodeId);
}

ControllerCommand* ChildrenCommand::clone() const
{
    return new ChildrenCommand(*this);
}