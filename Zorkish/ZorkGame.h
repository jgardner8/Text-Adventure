#pragma once

#include "CommandProcessor.h"
#include <string>

class ZorkGame {
private:
	CommandProcessor _cmdProcessor;
	Player _player;
	std::vector<Room> _map; //A centralised place to store and later delete rooms. Structure not used for game logic.

public:
	ZorkGame();

	void CreateWorld();
	std::string Run(); //returns reason for exiting (next state): { "MENU", "HIGHSCORES" }
};

