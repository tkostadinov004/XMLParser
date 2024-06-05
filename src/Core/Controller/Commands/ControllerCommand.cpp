#include "ControllerCommand.h"

ControllerCommand::ControllerCommand(XMLController& controller, const MyString& name, const MyVector<MyString>& arguments, size_t argumentsNeeded) : _controller(controller), _name(name)
{
	setArguments(arguments, argumentsNeeded);
}

void ControllerCommand::setArguments(const MyVector<MyString>& arguments, size_t argumentsNeeded)
{
	if (arguments.size() < argumentsNeeded)
	{
		throw std::invalid_argument(ErrorMessageBuilder::INSUFFICIENT_ARGUMENTS_FOR(_name).c_str());
	}
	_arguments = arguments;
}
