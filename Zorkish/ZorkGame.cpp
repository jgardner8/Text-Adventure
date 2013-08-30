#include "ZorkGame.h"
#include "Input.h"
#include <iostream>

using namespace std;

ZorkGame::ZorkGame() {
}

string ZorkGame::Run() {
	cout << "Welcome to Zorkish!" << endl
	     << "Enter menu to go back to the main menu at any time." << endl << endl;

	string input;
	do {
		input = GetInputStrBlocking();

	} while (input != "MENU" && input != "HIGHSCORES");

	return input;
}