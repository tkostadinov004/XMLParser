#pragma once
#include <iostream>
#include "XMLController.h"
#include "XPathController.h"
#include "../Utils/Messages/OutputMessages.h"

class Engine
{
	XMLController _xmlController;
	XPathController _xPathController;

	void handleCommandLine(const MyVector<MyString>& commandLine);
public:
	void run();
};