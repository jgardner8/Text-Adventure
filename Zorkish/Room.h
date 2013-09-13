#pragma once

#include <unordered_map>
#include <string>
#include "aEntity.h"

class Trap;
class Player;

enum class Direction {
	Invalid,
	North,
	South,
	East,
	West,
	Up,
	Down
};

class Room : public aEntity {
private:
	std::string _desc;
	std::unordered_map<Direction, Room*> _adjacencies;
	std::vector<Trap*> _traps; //used for the sole purpose of freeing their memory when the room is destroyed.

	Direction GetOppositeDirection(Direction dir);

public:
	Room(std::string desc);
	virtual ~Room();

	bool ConnectTo(Room *room, Direction direction); //returns success
	bool ConnectTo(Room *room, std::string direction); //returns success
	bool MovePlayer(Player &player, std::string directionStr); //returns success
	Direction StrToDirection(std::string dir);

	void AddTrap(Trap *trap) { _traps.push_back(trap); }
	std::string desc() { return _desc; }
};