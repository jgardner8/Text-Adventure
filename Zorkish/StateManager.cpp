#include "StateManager.h"
#include "Input.h"
#include <iostream>

using namespace std;

StateManager::StateManager() {
	CurrentState = &StateManager::MenuState;
	_currentAdventure = ' '; //null adventure
}

StateManager::~StateManager() {
	if (_currentAdventure != ' ')
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
		CurrentState = &StateManager::AboutState;
		break;
	case 'H':
		CurrentState = &StateManager::HelpState;
		break;
	case 'S':
		CurrentState = &StateManager::SelectAdventureState;
		break;
	case 'F':
		CurrentState = &StateManager::HallOfFameState;
		break;
	case 'Q':
		CurrentState = nullptr; //exit state manager (and effectively, the game)
		break;
	}
}

void StateManager::AboutState() {
	cout << "About State" << endl
		 << "\t[Q]uit" << endl;

	if (GetInputBlocking() == 'Q')
		CurrentState = &StateManager::MenuState;
}

void StateManager::HelpState() {
	cout << "Help State" << endl
	     << "\t[Q]uit" << endl;

	if (GetInputBlocking() == 'Q')
		CurrentState = &StateManager::MenuState;
}

void StateManager::SelectAdventureState() {
	cout << "Select Adventure State" << endl
		 << "\t[E]pic" << endl
		 << "\t[N]ot so epic" << endl
	     << "\t[Q]uit" << endl;

	char input = GetInputBlocking();
	if (input == 'E' || input == 'N') {
		if (_currentAdventure != input) {
			if (_currentAdventure != ' ') //null adventure
				delete _zorkGame;
			_zorkGame = new ZorkGame(this);
			_currentAdventure = input;
		}
		CurrentState = &StateManager::GameplayState;
	} else if (input == 'Q')
		CurrentState = &StateManager::MenuState;
}

void StateManager::GameplayState() {
	_zorkGame->Run();	
}

void StateManager::HighScoreState() {
	cout << "High Score State" << endl
	     << "\t[Q]uit" << endl;

	if (GetInputBlocking() == 'Q')
		CurrentState = &StateManager::MenuState;
}

void StateManager::HallOfFameState() {
	cout << "Hall of Fame State" << endl
	     << "\t[Q]uit" << endl;

	if (GetInputBlocking() == 'Q')
		CurrentState = &StateManager::MenuState;
}

void StateManager::Run() {
	while (CurrentState != nullptr) {
		cout << endl << "----------------------------" << endl;
		(this->*CurrentState)();		
	}
}