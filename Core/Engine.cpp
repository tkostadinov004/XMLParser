#include "Engine.h"
#include "..\Utils\MyVector\MyVector.hpp"

void Engine::run() const
{
	MyString input;
	getline(std::cin, input, 2048);

	while (input != "exit")
	{
		while (input.empty())
		{
			getline(std::cin, input, 2048);
		}
		MyVector<MyString> cmdLine = split(input);
		std::cout << 1;
		getline(std::cin, input, 2048);
	}
}
