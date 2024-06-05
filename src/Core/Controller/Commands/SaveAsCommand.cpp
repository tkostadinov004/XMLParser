#include "SaveAsCommand.h"

SaveAsCommand::SaveAsCommand(XMLController& controller, const MyVector<MyString>& arguments) : ControllerCommand(controller, "saveas", arguments, 1)
{
}

void SaveAsCommand::execute() const
{
    const MyString& path = _arguments[0];
    _controller.saveAs(path);
}

ControllerCommand* SaveAsCommand::clone() const
{
    return new SaveAsCommand(*this);
}