#include "ChildCommand.h"
#include "..\..\..\Utils\HelperFunctions.h"

ChildCommand::ChildCommand(XMLController& controller, const MyVector<MyString>& arguments) : ControllerCommand(controller, "child", arguments, 2)
{
}

void ChildCommand::execute() const
{
    const MyString& nodeId = _arguments[0];
    int childIndex = HelperFunctions::parseInteger(_arguments[1]);

    _controller.printNthChild(nodeId, childIndex);
}

ControllerCommand* ChildCommand::clone() const
{
    return new ChildCommand(*this);
}
