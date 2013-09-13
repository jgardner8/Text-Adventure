#pragma once

#include <string>
#include "CommandProcessor.h"
#include "ZorkGameFactory.h"
#include "Room.h"

class ZorkGame {
friend class ZorkGameFactory;
private:
	CommandProcessor _cmdProcessor;
	Player _player;
	std::vector<Room> _map; //A centralised place to store and later delete rooms. Structure not used for game logic.

public:
	std::string Run(); //returns reason for exiting (next state): { "MENU", "HIGHSCORES" }
};