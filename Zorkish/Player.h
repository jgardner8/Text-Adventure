#pragma once

#include "Room.h"
#include "aEntity.h"

class Room;

class Player : public aEntity {
private:
	Room *_location;

public:
	Player(Room *location=nullptr);

	Room* location() { return _location; }
	void location(Room *newLocation) { _location = newLocation; }
};

