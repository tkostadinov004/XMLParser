#include "Engine.h"
#include "..\Utils\HelperFunctions.h"
#include "Controller\Commands\ControllerCommand.h"
#include "Controller\ControllerCommandFactory.h"

static MyVector<MyString> splitCommandLine(const MyString& str)
{
	MyVector<MyString> result;
	MyString current;
	bool isInQuotes = false;

	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] == '\"')
		{
			isInQuotes = !isInQuotes;
			if (!isInQuotes && !current.empty())
			{
				result.push_back(current);
				current.clear();
			}
		}
		else if (str[i] == ' ' && !isInQuotes && !current.empty())
		{
			result.push_back(current);
			current.clear();
		}
		else
		{
			current += str[i];
		}
	}
	if (!current.empty())
	{
		result.push_back(current);
	}

	return result;
}
void Engine::handleCommandLine(const MyVector<MyString>& commandLine)
{
	if (commandLine.empty())
	{
		return;
	}

	const MyString& commandName = commandLine.front();

	ControllerCommandFactory factory;
	try
	{
		MySharedPtr<ControllerCommand> command = factory.create(_xmlController, commandName, commandLine.skip(1));
		command->execute();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}

Engine& Engine::getInstance()
{
	static Engine engine;
	return engine;
}

void Engine::run()
{
	MyString input;
	getline(std::cin, input, 2048);

	while (input != "exit")
	{
		while (input.empty())
		{
			getline(std::cin, input, 2048);
		}
		MyVector<MyString> commandLine = splitCommandLine(input);

		handleCommandLine(commandLine);

		getline(std::cin, input, 2048);
	}
	std::cout << "Exiting the program..." << std::endl;
}
