#pragma once
#include <iostream>
#include "XMLController.h"
#include "../Utils/Messages/OutputMessages.h"

class Engine
{
	XMLController _xmlController;

	void handleCommandLine(const MyVector<MyString>& commandLine);
public:
	void run();
};