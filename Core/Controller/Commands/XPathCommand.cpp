#include "XPathCommand.h"

XPathCommand::XPathCommand(XMLController& controller, const MyVector<MyString>& arguments) : ControllerCommand(controller, "xpath", arguments, 1)
{
}

void XPathCommand::execute() const
{
    MyString query = _arguments[0];
    _controller.handleXPath(query);
}

ControllerCommand* XPathCommand::clone() const
{
    return new XPathCommand(*this);
}