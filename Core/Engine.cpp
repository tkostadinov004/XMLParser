#include "Engine.h"
#include "..\Utils\HelperFunctions.h"

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

	const MyString& command = commandLine.front();
	if (command == "open")
	{
		const MyString& path = commandLine[1];

		_xmlController.openFile(path);
	}
	else if (command == "close")
	{
		_xmlController.closeFile();
	}
	else if (command == "save")
	{
		_xmlController.save();
	}
	else if (command == "saveas")
	{
		const MyString& path = commandLine[1];

		_xmlController.saveAs(path);
	}
	else if (command == "help")
	{
		_xmlController.help();
	}
	else if (command == "print")
	{
		_xmlController.print();
	}
	else if (command == "cls")
	{
		system("cls");
	}
	else if (command == "select")
	{
		const MyString& nodeId = commandLine[1];
		const MyString& attributeName = commandLine[2];

		_xmlController.selectAttribute(nodeId, attributeName);
	}
	else if (command == "set")
	{
		const MyString& nodeId = commandLine[1];
		const MyString& attributeName = commandLine[2];
		const MyString& newValue = commandLine[3];

		_xmlController.changeAttributeValue(nodeId, attributeName, newValue);
	}
	else if (command == "children")
	{
		const MyString& nodeId = commandLine[1];

		_xmlController.printChildrenOfNode(nodeId);
	}
	else if (command == "child")
	{
		const MyString& nodeId = commandLine[1];
		int childIndex = HelperFunctions::parseInteger(commandLine[2]);

		_xmlController.printNthChild(nodeId, childIndex);
	}
	else if (command == "text")
	{
		const MyString& nodeId = commandLine[1];

		_xmlController.printInnerText(nodeId);
	}
	else if (command == "delete")
	{
		const MyString& nodeId = commandLine[1];
		const MyString& attributeName = commandLine[2];

		_xmlController.deleteAttribute(nodeId, attributeName);
	}
	else if (command == "newchild")
	{
		const MyString& nodeId = commandLine[1];

		_xmlController.addChild(nodeId);
	}
	else if (command == "xpath")
	{
		MyString query = commandLine[1];
		_xmlController.handleXPath(query);
	}
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

		try
		{
			handleCommandLine(commandLine);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}

		getline(std::cin, input, 2048);
	}
	std::cout << "Exiting the program..." << std::endl;
}
