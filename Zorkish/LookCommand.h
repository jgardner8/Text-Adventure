#pragma once

#include "aCommand.h"
#include "Inventory.h"

class LookCommand : public aCommand {
public:
	std::string LookCommand::LookAtItem(Player &player, Inventory *roomContents, const std::vector<std::string> *cmd); 
	std::string LookCommand::LookInItem(Player &player, Inventory *roomContents, const std::vector<std::string> *cmd);
	std::string LookCommand::LookAtItemInItem(Player &player, Inventory *roomContents, const std::vector<std::string> *cmd);

	virtual std::string Execute(Player &player, const std::vector<std::string> *cmd) override; //returns msg intended for user
};

 