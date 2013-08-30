#pragma once

#include "aComponent.h"
#include <functional>

class Health : public aComponent {
private:
	int _health;
	std::function<void()> _callOnDeath;

public:
	Health(int startHealth, std::function<void()> callOnDeath);

	bool IsAlive() { return _health > 0; }
	void Hurt(int amount);
};

