#pragma once

#include <unordered_map>
#include <string>
#include "Player.h"
#include "aEntity.h"

enum class Direction {
	Invalid,
	North,
	South,
	East,
	West,
	Up,
	Down
};

class Player;

class Room : public aEntity {
private:
	std::string _desc;
	std::unordered_map<Direction, Room*> _adjacencies;

	Direction GetOppositeDirection(Direction dir);

public:
	Room(std::string desc);
	virtual ~Room();

	bool ConnectTo(Room *room, Direction direction); //returns success
	bool MovePlayer(Player &player, std::string directionStr); //returns success

	std::string desc() { return _desc; }
};