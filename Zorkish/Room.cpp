#include "Room.h"

using namespace std;

Room::Room() {

}

Room::~Room() {
	//Destroy all links back to here
	for (auto kvp : _adjacencies) 
		kvp.second->_adjacencies.erase(GetOppositeDirection(kvp.first));
}

Direction Room::GetOppositeDirection(Direction dir) {
	return (Direction)(((int)dir & 1) == 0 ? (int)dir + 1 : (int)dir - 1);
}

bool Room::ConnectTo(Room *room, Direction direction) {	
	Direction opposite = GetOppositeDirection(direction);

	if (_adjacencies.find(direction) != _adjacencies.end()
	 || room->_adjacencies.find(opposite) != room->_adjacencies.end())
		return false;

	_adjacencies[direction] = room;
	room->_adjacencies[opposite] = this;
	return true;
}

bool Room::MovePlayer(Player &player, string directionStr) {
	Direction direction = 
	    (directionStr == "NORTH" || directionStr == "N") ? Direction::North 
	  : (directionStr == "SOUTH" || directionStr == "S") ? Direction::South
	  : (directionStr == "EAST" || directionStr == "E") ? Direction::East
	  : (directionStr == "WEST" || directionStr == "W") ? Direction::West
	  : (directionStr == "UP" || directionStr == "U") ? Direction::Up
	  : (directionStr == "DOWN" || directionStr == "D") ? Direction::Down
	  : Direction::Invalid;
	if (direction == Direction::Invalid || _adjacencies.find(direction) == _adjacencies.end())
		return false;
	
	player.location(_adjacencies[direction]);
	return true;
}