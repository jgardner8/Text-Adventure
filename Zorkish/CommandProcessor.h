#pragma once

#include "Player.h"
#include "aCommand.h"
#include <unordered_map>

class CommandProcessor {
private:
	std::unordered_map<std::string, aCommand*> _commands;

public:
	CommandProcessor();
	~CommandProcessor();

	std::string Process(Player &player, const std::string &input); //returns msg intended for user
};