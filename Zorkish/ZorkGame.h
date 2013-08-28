#pragma once

#include "StateManager.h"

class StateManager;

//PROOF OF CONCEPT ONLY
class ZorkGame {
private:
	StateManager *_stateMngr;
	int _score;

public:
	ZorkGame(StateManager *_stateMngr);

	void Run();
};

