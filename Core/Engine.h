#pragma once
#include <iostream>
#include "XMLController.h"
#include "../Utils/Messages/OutputMessages.h"

class Engine
{
	XMLController _xmlController;
	Engine() = default;

	void handleCommandLine(const MyVector<MyString>& commandLine);
public:
	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;
	static Engine& getInstance();
	void run();
};