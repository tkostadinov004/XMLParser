#include "TextCommand.h"

TextCommand::TextCommand(XMLController& controller, const MyVector<MyString>& arguments) : ControllerCommand(controller, "text", arguments, 1)
{
}

void TextCommand::execute() const
{
	const MyString& nodeId = _arguments[0];

	_controller.printInnerText(nodeId);
}

ControllerCommand* TextCommand::clone() const
{
	return new TextCommand(*this);
}