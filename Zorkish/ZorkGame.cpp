#include "ZorkGame.h"
#include "Input.h"
#include "Item.h"
#include "Inventory.h"
#include "Health.h"
#include <iostream>

using namespace std;

ZorkGame::ZorkGame() {
	CreateWorld();
}

void ZorkGame::CreateWorld() {
	_map.push_back(Room("Appears to be some sort of courtyard. There's a house to the north and a sword hidden in the grass."));
	_map.push_back(Room("An old house with a fireplace. There is a bag in the corner and an exit to the south."));
	_map[0].ConnectTo(&_map[1], Direction::North);
	_player.location(&_map[0]);

	Item sword("sword", "A large broadsword with a rusty blade");
	Item bag("bag", "A blue school bag");
	Inventory *bagContents = new Inventory();
	bag.AddComponent(bagContents);
	Item paper("paper", "A sheet of clearly recycled paper");
	bagContents->Add(paper);

	Item box("box", "A small box");
	Inventory *boxContents = new Inventory();
	box.AddComponent(boxContents);
	Item cards("cards", "A deck of worn playing cards");
	boxContents->Add(cards);
	bagContents->Add(box);

	Inventory *roomContents = (Inventory*)_map[0].GetComponent("INVENTORY");
	roomContents->Add(sword);
	roomContents = (Inventory*)_map[1].GetComponent("INVENTORY");
	roomContents->Add(bag);
}

string ZorkGame::Run() {
	cout << "Welcome to Zorkish!" << endl
	     << "Enter menu to go back to the main menu at any time." << endl << endl;
	FlushCin();

	cout << _player.location()->desc() << endl;
	
	string input, output;
	do {
		input = GetInputStrBlocking();
		output = _cmdProcessor.Process(_player, input);
		cout << endl << output << endl;
	} while (output != "Pausing...");

	return input;
}