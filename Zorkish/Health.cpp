#include "Health.h"

Health::Health(int startHealth, std::function<void()> callOnDeath) : aComponent("health") {
	_health = startHealth;
	_callOnDeath = callOnDeath;
}

void Health::Hurt(int amount) {
	_health -= amount;
	if (!IsAlive())
		_callOnDeath();
}