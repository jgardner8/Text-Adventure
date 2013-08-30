#include "Player.h"
#include "Inventory.h"
#include "Health.h"
#include "Damage.h"
#include <iostream>

using namespace std;

Player::Player(Room *location) {
	_location = location;
	AddComponent(Inventory());
	AddComponent(Health(100, [](){ cout << "You're dead!"; }));
	AddComponent(Damage(10, 20));
}