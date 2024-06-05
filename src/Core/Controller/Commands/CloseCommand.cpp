#include "CloseCommand.h"

CloseCommand::CloseCommand(XMLController& controller, const MyVector<MyString>& arguments) : ControllerCommand(controller, "close", arguments, 0)
{
}

void CloseCommand::execute() const
{
    _controller.closeFile();
}

ControllerCommand* CloseCommand::clone() const
{
    return new CloseCommand(*this);
}