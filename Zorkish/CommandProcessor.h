#pragma once

#include "Command.h"
#include <map>

class CommandProcessor {
private:
	std::map<std::string, Command*> _commands;

public:
	CommandProcessor();
	~CommandProcessor();

	std::string CommandProcessor::Process(World &world, const std::string &input); //returns error, or "" on success
};

