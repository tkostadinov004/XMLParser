#include "Engine.h"

static MyVector<MyString> splitCommandLine(const MyString& str) {
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
MyString Engine::handleCommandLine(const MyVector<MyString>& commandLine)
{
	if (commandLine.empty())
	{
		return MyString();
	}

	MyString result;
	const MyString& command = commandLine.front();
	if (command == "open")
	{
		const MyString& path = commandLine[1];
		result = _xmlController.openFile(path);
	}
	else if (command == "close")
	{
		result = _xmlController.closeFile();
	}
	else if (command == "save")
	{
		result = _xmlController.save();
	}
	else if (command == "saveas")
	{
		const MyString& path = commandLine[1];
		result = _xmlController.saveAs(path);
	}
	else if (command == "help")
	{
		result = _xmlController.help();
	}
	return result;
}

void Engine::run()
{
	MyString input;
	getline(std::cin, input, 2048);

	MyString result;
	while (input != "exit")
	{
		while (input.empty())
		{
			getline(std::cin, input, 2048);
		}
		MyVector<MyString> commandLine = splitCommandLine(input);

		result = handleCommandLine(commandLine);
		std::cout << result << std::endl;

		getline(std::cin, input, 2048);
	}
}
