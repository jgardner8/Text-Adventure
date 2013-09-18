#pragma once

#include "ZorkGame.h"

class StateManager {
private:
	std::string _currentAdventure;
	ZorkGame *_zorkGame;

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

	std::vector<std::string> GetWorldList(); //used to get list of world files for SelectAdventureState()

public:
	StateManager();
	virtual ~StateManager();

	void Run();
};