#pragma once

#include "aCommand.h"

class InventoryCommand : public aCommand {
public:
	virtual std::string Execute(Player &player, const std::vector<std::string> *cmd) override; //returns msg intended for user
};

