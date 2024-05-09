#pragma once

#include <iostream>
#include "Controller.h"
#include "FileManager.hpp"

class Engine
{
	Controller _controller;
	FileManager _fileManager;
public:
	void run() const;
};