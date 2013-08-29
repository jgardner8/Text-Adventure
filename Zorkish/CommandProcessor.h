#pragma once

#include "ZorkGame.h"
#include "Command.h"
#include <map>

class CommandProcessor {
private:
	std::map<std::string, Command*> _commands;

public:
	CommandProcessor();
	~CommandProcessor();

	std::string CommandProcessor::Process(ZorkGame *zorkGame, const std::string &input); //returns error, or "" on success
};

