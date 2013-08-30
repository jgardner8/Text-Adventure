#pragma once

#include "Player.h"
#include <string>
#include <vector>

class ZorkGame;

class aCommand {
public:
	virtual std::string Execute(Player &player, const std::vector<std::string> *cmd) = 0; //returns error or success msg
};