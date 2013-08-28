#pragma once

#include "ZorkGame.h"

class ZorkGame;

class StateManager {
private:
	char _currentAdventure;
	ZorkGame *_zorkGame; //because of circular reference this must be a pointer
	friend ZorkGame;

	//State Pointer
	void (StateManager::*CurrentState)(); //points to the current state function
	//State Methods
	void MenuState(); //default
	void AboutState();
	void HelpState();
	void SelectAdventureState();
	void GameplayState();
	void HighScoreState();
	void HallOfFameState();

public:
	StateManager();
	~StateManager();

	void Run();
};