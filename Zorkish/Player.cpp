#include "Player.h"
#include "Inventory.h"
#include "Health.h"
#include "Damage.h"
#include <iostream>

using namespace std;

Player::Player(Room *location) {
	_location = location;
	AddComponent(new Inventory());
	AddComponent(new Health(100, [](){ cout << "You're dead!"; }));
	AddComponent(new Damage(10, 20));
}