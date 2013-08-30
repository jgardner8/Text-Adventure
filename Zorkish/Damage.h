#pragma once

#include "aComponent.h"
#include "Health.h"

class Damage : public aComponent {
private:
	int _minDamage, _maxDamage;

public:
	Damage(int minDamage, int maxDamage);
	int Attack(Health health); //returns damage done 
};

