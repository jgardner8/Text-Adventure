#include "Player.h"
#include "Inventory.h"
#include "Health.h"
#include "Damage.h"
#include <iostream>

using namespace std;

Player::Player(Room *location, int startHealth) {
	_location = location;
	AddComponent(new Inventory());
	AddComponent(new Health(startHealth, [](){ cout << "You're dead!" << endl; }));
	AddComponent(new Damage(10, 20));
}