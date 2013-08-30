#include "ZorkGame.h"
#include "Input.h"
#include <iostream>

using namespace std;

ZorkGame::ZorkGame() {
	CreateWorld();
}

void ZorkGame::CreateWorld() {
	_map.push_back(Room("Appears to be some sort of courtyard. There's a house to the north."));
	_map.push_back(Room("An old house with a fireplace. There's a deck of stained cards on the floor and a door to the south."));
	_map[0].ConnectTo(&_map[1], Direction::North);
	_player.location(&_map[0]);
}

string ZorkGame::Run() {
	cout << "Welcome to Zorkish!" << endl
	     << "Enter menu to go back to the main menu at any time." << endl << endl;
	FlushCin();

	string input, output;
	do {
		cout << _player.location()->desc() << endl;
		input = GetInputStrBlocking();
		output = _cmdProcessor.Process(_player, input);
		cout << output << endl << endl;
	} while (output != "Pausing...");

	return input;
}