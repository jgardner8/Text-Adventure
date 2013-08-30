#include "StateManager.h"
#include "Input.h"
#include <iostream>

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

void StateManager::SelectAdventureState() {
	cout << "Select Adventure State" << endl
		 << "\t[E]pic" << endl
		 << "\t[N]ot so epic" << endl
	     << "\t[Q]uit" << endl;

	char input = GetInputBlocking();
	if (input == 'E' || input == 'N') {
		if (_currentAdventure != input) {
			if (_zorkGame != nullptr)
				delete _zorkGame;
			_zorkGame = new ZorkGame(); 
			_currentAdventure = input;
		}
		_currentState = &StateManager::GameplayState;
	} else if (input == 'Q')
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