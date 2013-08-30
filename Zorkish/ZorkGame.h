#pragma once

#include <unordered_map>
#include "aCommand.h"
#include <string>

class ZorkGame {
private:
	std::unordered_map<std::string, aCommand*> _commands;

public:
	ZorkGame();

	std::string Run(); //returns reason for exiting (next state): { "MENU", "HIGHSCORES" }
};

