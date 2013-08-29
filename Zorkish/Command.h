#pragma once

#include "ZorkGame.h"
#include <string>
#include <vector>

class Command {
public:
	Command();
	virtual std::string Execute(ZorkGame *zorkGame, const std::vector<std::string> *cmd) = 0; //returns error, or "" on success
};