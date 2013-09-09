#pragma once

//Not implemented. 
//Used only to set start values to demonstrate part of Configuration Pattern spike.
class Trap {
private:
	int _damage;
	bool _keyNeeded;

public:
	Trap(int damage, bool keyNeeded=false) {
		_damage = damage;
		_keyNeeded = keyNeeded;
	}
};