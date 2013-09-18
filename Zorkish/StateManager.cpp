#include <iostream>
#include <algorithm>
#include "StateManager.h"
#include "Input.h"
#include "ZorkGameFactory.h"
#include "StringFunc.h"
#include "lib/tinydir.h"

using namespace std;

StateManager::StateManager() {
	_currentState = &StateManager::MenuState;
	_currentAdventure = ' '; //null adventure
	_zorkGame = nullptr;
}

StateManager::~StateManager() {
	if (_zorkGame != nullptr)
		delete _zorkGame;
}

void StateManager::MenuState() {
	cout << "Menu State:" << endl
	     << "\t[A]bout" << endl 
		 << "\t[H]elp" << endl
		 << "\t[S]elect Adventure" << endl
		 << "\tHall of [F]ame" << endl
		 << "\t[Q]uit" << endl;

	switch (GetInputBlocking()) {
	case 'A':
		_currentState = &StateManager::AboutState;
		break;
	case 'H':
		_currentState = &StateManager::HelpState;
		break;
	case 'S':
		_currentState = &StateManager::SelectAdventureState;
		break;
	case 'F':
		_currentState = &StateManager::HallOfFameState;
		break;
	case 'Q':
		_currentState = nullptr; //exit state manager (and effectively, the game)
		break;
	}
}

void StateManager::AboutState() {
	cout << "About State" << endl
		 << "\t[Q]uit" << endl;

	if (GetInputBlocking() == 'Q')
		_currentState = &StateManager::MenuState;
}

void StateManager::HelpState() {
	cout << "Help State" << endl
	     << "\t[Q]uit" << endl;

	if (GetInputBlocking() == 'Q')
		_currentState = &StateManager::MenuState;
}

vector<string> StateManager::GetWorldList() {
	tinydir_dir dir;
	tinydir_open(&dir, "worlds/");

	vector<string> worldNames;
	while (dir.has_next)
	{
		tinydir_file file;
		tinydir_readfile(&dir, &file);

		if (!file.is_dir) {
			string name(file.name);
			worldNames.push_back(name.substr(0, name.length() - 4)); //remove .xml
		}

		tinydir_next(&dir);
	}

	tinydir_close(&dir);
	return worldNames;
}

void StateManager::SelectAdventureState() {
	cout << "Select a world:" << endl;
	vector<string> worldNames = GetWorldList();
	for (string s : worldNames)
		cout << "\t" << s << endl;
	cout << endl << "[Q]uit" << endl;

	string input = GetInputStrBlocking();
	//if input is valid world
	if (find_if(begin(worldNames), end(worldNames), [&input] (string world) { return input == ToUpper(world); }) != end(worldNames)) {
		if (_currentAdventure != input) {
			if (_zorkGame)
				delete _zorkGame;
			_zorkGame = ZorkGameFactory::FromFile(input); 
			_currentAdventure = input;
		}
		_currentState = &StateManager::GameplayState;
	} else if (input == "Q" || input == "QUIT")
		_currentState = &StateManager::MenuState;
}

void StateManager::GameplayState() {
	string exitReason = _zorkGame->Run();
	_currentState = exitReason[0] == 'H' ? &StateManager::HighScoreState : &StateManager::MenuState;
}

void StateManager::HighScoreState() {
	cout << "High Score State" << endl
	     << "\t[Q]uit" << endl;

	if (GetInputBlocking() == 'Q')
		_currentState = &StateManager::MenuState;
}

void StateManager::HallOfFameState() {
	cout << "Hall of Fame State" << endl
	     << "\t[Q]uit" << endl;

	if (GetInputBlocking() == 'Q')
		_currentState = &StateManager::MenuState;
}

void StateManager::Run() {
	while (_currentState != nullptr) {
		cout << endl << "----------------------------" << endl;
		(this->*_currentState)();		
	}
}