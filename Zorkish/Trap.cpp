#include "Trap.h"

Trap::Trap(Room *location, int damage, bool keyNeeded) {
	_location = location;
	_damage = damage;
	_keyNeeded = keyNeeded;
}

void Trap::Handle(PlayerMovedMessage *message) {
	if (_location == message->_sender->location() && rand() % 3 == 0) {
		Health *health = (Health*)message->_sender->GetComponent("HEALTH");
		std::cout << "You were dealt " << _damage << " damage by a trap!" << std::endl;
		health->Hurt(_damage);
	}
}