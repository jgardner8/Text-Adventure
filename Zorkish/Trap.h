#pragma once

#include <iostream>
#include <random>
#include "aMessageHandler.h"
#include "Player.h"
#include "PlayerMovedMessage.h"
#include "Health.h"

class Room;

class Trap : public aMessageHandler<PlayerMovedMessage> {
private:
	Room *_location;
	int _damage;
	bool _keyNeeded;

public:
	Trap(Room *location, int damage, bool keyNeeded=false);
	virtual void Handle(PlayerMovedMessage *message) override;
};