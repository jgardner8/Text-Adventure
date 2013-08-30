#pragma once

#include "aCommand.h"

class MoveCommand : public aCommand {
public:
	virtual std::string Execute(Player &player, const std::vector<std::string> *cmd) override; //returns error or success msg
};

