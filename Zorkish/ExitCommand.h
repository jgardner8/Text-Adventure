#pragma once

#include "aCommand.h"

class ExitCommand : public aCommand {
public:
	virtual std::string Execute(Player &player, const std::vector<std::string> *cmd) override {
		//The real functionality is implemented as a loop exit in ZorkGame.cpp.
		//This just ensures that the CommandProcessor does not say it doesn't recognise the command.
		return "Pausing..."; 
	}	 
};

