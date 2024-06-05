#include "ControllerCommandFactory.h"
#include "Commands/ChildCommand.h"
#include "Commands/ChildrenCommand.h"
#include "Commands/CloseCommand.h"
#include "Commands/DeleteCommand.h"
#include "Commands/HelpCommand.h"
#include "Commands/NewChildCommand.h"
#include "Commands/OpenCommand.h"
#include "Commands/PrintCommand.h"
#include "Commands/SaveAsCommand.h"
#include "Commands/SaveCommand.h"
#include "Commands/SelectCommand.h"
#include "Commands/SetCommand.h"
#include "Commands/SetCommand.h"
#include "Commands/TextCommand.h"
#include "Commands/XPathCommand.h"

MySharedPtr<ControllerCommand> ControllerCommandFactory::create(XMLController& controller, const MyString& commandName, const MyVector<MyString>& arguments) const
{
	MySharedPtr<ControllerCommand> result = nullptr;
	if (commandName == "open")
	{
		result = new OpenCommand(controller, arguments);
	}
	else if (commandName == "close")
	{
		result = new CloseCommand(controller, arguments);
	}
	else if (commandName == "save")
	{
		result = new SaveCommand(controller, arguments);
	}
	else if (commandName == "saveas")
	{
		result = new SaveAsCommand(controller, arguments);
	}
	else if (commandName == "help")
	{
		result = new HelpCommand(controller, arguments);
	}
	else if (commandName == "print")
	{
		result = new PrintCommand(controller, arguments);
	}
	else if (commandName == "select")
	{
		result = new SelectCommand(controller, arguments);
	}
	else if (commandName == "set")
	{
		result = new SetCommand(controller, arguments);
	}
	else if (commandName == "children")
	{
		result = new ChildrenCommand(controller, arguments);
	}
	else if (commandName == "child")
	{
		result = new ChildCommand(controller, arguments);
	}
	else if (commandName == "text")
	{
		result = new TextCommand(controller, arguments);
	}
	else if (commandName == "delete")
	{
		result = new DeleteCommand(controller, arguments);
	}
	else if (commandName == "newchild")
	{
		result = new NewChildCommand(controller, arguments);
	}
	else if (commandName == "xpath")
	{
		result = new XPathCommand(controller, arguments);
	}
	else
	{
		throw std::invalid_argument(ErrorMessageBuilder::INVALID_COMMAND_NAME());
	}
	return result;
}