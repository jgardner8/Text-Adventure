#pragma once

#include "ZorkGame.h"

class StateManager {
private:
	char _currentAdventure;
	ZorkGame _zorkGame;

	//State Pointer
	void (StateManager::*_currentState)(); //points to the current state function
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

	void Run();
};