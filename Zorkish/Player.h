#pragma once

#include "Room.h"

class Room;

class Player {
private:
	Room *_location;

public:
	Player(Room *location);

	Room* location() { return _location; }
	void location(Room *newLocation) { _location = newLocation; }
};

