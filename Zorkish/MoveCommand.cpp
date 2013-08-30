#include "MoveCommand.h"

using namespace std;

string MoveCommand::Execute(Player &player, const vector<string> *cmd) { //returns error or success msg
	//Two different vocabularies (where <cmd> is simply calling this command):
	//- <cmd> DIRECTION
	//- DIRECTION
	string directionStr = cmd->size() == 1 ? (*cmd)[0] : (*cmd)[1];
	if (player.location()->MovePlayer(player, directionStr))
		return player.location()->desc();
	else
		return "You cannot move in that direction.";
}