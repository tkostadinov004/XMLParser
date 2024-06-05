#include "PrintCommand.h"

PrintCommand::PrintCommand(XMLController& controller, const MyVector<MyString>& arguments) : ControllerCommand(controller, "print", arguments, 0)
{
}

void PrintCommand::execute() const
{
    _controller.print();
}

ControllerCommand* PrintCommand::clone() const
{
    return new PrintCommand(*this);
}