#include "TakeCommand.h"
#include "Room.h"

using namespace std;

string TakeCommand::TakeItem(Player &player, Inventory *roomContents, Inventory *playerInventory, const vector<string> *cmd) {
	if (!roomContents->Contains((*cmd)[1]))
		return "I cannot find the " + (*cmd)[1];
	Item item = *roomContents->GetItem((*cmd)[1]);
	roomContents->Remove((*cmd)[1]);
	playerInventory->Add(item);
	return "You have taken the " + (*cmd)[1];
}

string TakeCommand::TakeItemFromItem(Player &player, Inventory *roomContents, Inventory *playerInventory, const vector<string> *cmd) {
	Item *takeFrom = roomContents->GetItem((*cmd)[3]);		
	if (takeFrom == nullptr)
		return "I cannot find the " + (*cmd)[3];
	
	Inventory *takeFromContents = (Inventory*)takeFrom->GetComponent("INVENTORY");
	if (!takeFromContents->Contains((*cmd)[1]))
		return "There is no " + (*cmd)[1] + " in the " + (*cmd)[3];
	Item toTake = *takeFromContents->GetItem((*cmd)[1]);

	takeFromContents->Remove((*cmd)[1]);
	playerInventory->Add(toTake);
	return "You have taken the " + (*cmd)[1] + " from the " + (*cmd)[3];
}

string TakeCommand::Execute(Player &player, const vector<string> *cmd) {
	//Two different vocabularies (where <cmd> is simply calling this command):
	//- <cmd> ITEM (takes item from current room)
	//- <cmd> ITEM1 from ITEM2 (takes item from inside another item)
	Inventory *roomContents = (Inventory*)player.location()->GetComponent("INVENTORY");
	Inventory *playerInventory = (Inventory*)player.GetComponent("INVENTORY");
	if (cmd->size() == 2)
		return TakeItem(player, roomContents, playerInventory, cmd);
	else if (cmd->size() == 4)
		return TakeItemFromItem(player, roomContents, playerInventory, cmd);
	return "Syntax is one of: take ITEM, take ITEM1 from ITEM2";
}