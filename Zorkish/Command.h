#pragma once

#include "World.h"
#include <string>
#include <vector>

class Command {
public:
	Command();
	virtual std::string Execute(World &world, const std::vector<std::string> *cmd) = 0; //returns error, or "" on success
};