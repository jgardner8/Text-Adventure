#include "ZorkGame.h"
#include "Input.h"
#include <iostream>

using namespace std;

ZorkGame::ZorkGame(StateManager *stateMngr) {
	_score = 0;
	_stateMngr = stateMngr;
}

void ZorkGame::Run() {
	cout << "Gameplay State" << endl
	     << "\t[A]chieve high score" << endl
	     << "\t[Q]uit" << endl;

	char input;
	do {
		input = GetInputBlocking();
		cout << "Score: " << ++_score;
	} while (input != 'Q' && input != 'A');

	_stateMngr->CurrentState = (input == 'Q') ? &StateManager::MenuState : &StateManager::HighScoreState;
}