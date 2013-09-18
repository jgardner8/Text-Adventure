#include "ZorkGame.h"
#include "Input.h"
#include "Item.h"
#include "Inventory.h"
#include "Health.h"
#include "Room.h"
#include <iostream>

using namespace std;

string ZorkGame::Run() {
	cout << "Welcome to Zorkish!" << endl
	     << "Enter menu to go back to the main menu at any time." << endl << endl;

	cout << _player.location()->desc() << endl;
	
	string input, output;
	do {
		input = GetInputStrBlocking();
		output = _cmdProcessor.Process(_player, input);
		cout << endl << output << endl;
	} while (output != "Pausing...");

	return input;
}