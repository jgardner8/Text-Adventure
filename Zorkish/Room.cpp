#include "Room.h"
#include "Inventory.h"
#include <stdexcept>

using namespace std;

Room::Room(string desc) {
	AddComponent(new Inventory());
	_desc = desc;
}

Room::~Room() {
	//Destroy all links back to here
	for (auto kvp : _adjacencies) 
		kvp.second->_adjacencies.erase(GetOppositeDirection(kvp.first));
}

Direction Room::GetOppositeDirection(Direction dir) {
	if (dir == Direction::Invalid)
		throw invalid_argument("dir == Direction::Invalid");
	return (Direction)(((int)dir & 1) == 1 ? (int)dir + 1 : (int)dir - 1);
}

bool Room::ConnectTo(Room *room, Direction direction) {	
	if (direction == Direction::Invalid)
		return false;

	Direction opposite = GetOppositeDirection(direction);

	if (_adjacencies.find(direction) != _adjacencies.end()
	 || room->_adjacencies.find(opposite) != room->_adjacencies.end())
		return false;

	_adjacencies[direction] = room;
	room->_adjacencies[opposite] = this;
	return true;
}

bool Room::ConnectTo(Room *room, string direction) {	
	return ConnectTo(room, StrToDirection(direction));
}

Direction Room::StrToDirection(string dir) {
	return (dir == "NORTH" || dir == "N") ? Direction::North 
		 : (dir == "SOUTH" || dir == "S") ? Direction::South
		 : (dir == "EAST" || dir == "E") ? Direction::East
		 : (dir == "WEST" || dir == "W") ? Direction::West
		 : (dir == "UP" || dir == "U") ? Direction::Up
		 : (dir == "DOWN" || dir == "D") ? Direction::Down
		 : Direction::Invalid;
}

bool Room::MovePlayer(Player &player, string directionStr) {
	auto direction = StrToDirection(directionStr);

	if (direction == Direction::Invalid || _adjacencies.find(direction) == _adjacencies.end())
		return false;
	
	player.location(_adjacencies[direction]);
	return true;
}