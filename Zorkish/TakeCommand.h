#pragma once

#include "aCommand.h"
#include "Inventory.h"

class TakeCommand :	public aCommand {
public:
	std::string TakeItem(Player &player, Inventory *roomContents, Inventory *playerInventory, const std::vector<std::string> *cmd);
	std::string TakeItemFromItem(Player &player, Inventory *roomContents, Inventory *playerInventory, const std::vector<std::string> *cmd);

	virtual std::string Execute(Player &player, const std::vector<std::string> *cmd) override; //returns msg intended for user
};

