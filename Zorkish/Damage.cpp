#include "Damage.h"
#include "MathFunc.h"

Damage::Damage(int minDamage, int maxDamage) : aComponent("damage") {
	_minDamage = minDamage;
	_maxDamage = maxDamage;
}

int Damage::Attack(Health health) {
	int dmg = Random(_minDamage, _maxDamage);
	health.Hurt(dmg);
	return dmg;
}