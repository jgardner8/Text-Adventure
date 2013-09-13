#pragma once

class Player;

class PlayerMovedMessage {
public:
	Player *_sender;

	PlayerMovedMessage(Player *sender) {
		_sender = sender;
	}
};