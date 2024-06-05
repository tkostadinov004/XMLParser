#include "Core/Engine.h"

int main()
{
	MyVector<int> evens;
	for (size_t i = 0; i <= 10; i += 2)
	{
		evens.push_back(i);
	}
	std::cout << evens.count([](const int& a) {return a % 2 == 0;});

	Engine& engine = Engine::getInstance();
	engine.run();
}