#include "LookCommand.h"

using namespace std;

string LookCommand::LookAtItem(Player &player, Inventory *roomContents, const vector<string> *cmd) {
	Item *item = roomContents->GetItem((*cmd)[2]);
	return item != nullptr ? item->longDesc() : "I cannot find the " + (*cmd)[2];
}

string LookCommand::LookInItem(Player &player, Inventory *roomContents, const vector<string> *cmd) {
	Item *item = roomContents->GetItem((*cmd)[2]);
	if (item == nullptr)
		return "I cannot find the " + (*cmd)[2];
	
	Inventory *itemContents = (Inventory*)item->GetComponent("INVENTORY");
	return itemContents != nullptr 
		? "The " + (*cmd)[2] + " contains:\n" + itemContents->Contents() 
		: "The " + (*cmd)[2] + " is not capable of containing items";
}

string LookCommand::LookAtItemInItem(Player &player, Inventory *roomContents, const vector<string> *cmd) {
	Item *lookIn = roomContents->GetItem((*cmd)[4]);
	if (lookIn == nullptr)
		return "I cannot find the " + (*cmd)[2];
	
	Inventory *itemContents = (Inventory*)lookIn->GetComponent("INVENTORY");
	if (itemContents == nullptr)
		return "The " + (*cmd)[4] + " is not capable of containing items";
	
	Item *lookAt = itemContents->GetItem((*cmd)[2]);
	return lookAt != nullptr ? lookAt->longDesc() : "There is no " + (*cmd)[2] + " in the " + (*cmd)[4];
}

string LookCommand::Execute(Player &player, const vector<string> *cmd) {
	//Three different vocabularies (where <cmd> is simply calling this command):
	//- <cmd> at ITEM
	//- <cmd> in ITEM (must have inventory component)
	//- <cmd> at ITEM1 in ITEM2 (ITEM2 must have inventory component)
	Inventory *roomContents = (Inventory*)player.location()->GetComponent("INVENTORY");
	if (cmd->size() == 5)
		return LookAtItemInItem(player, roomContents, cmd);
	if (cmd->size() == 3) {
		if ((*cmd)[1] == "IN")
			return LookInItem(player, roomContents, cmd);
		if ((*cmd)[1] == "AT")
			return LookAtItem(player, roomContents, cmd);
	}
	return "Syntax is one of: look at ITEM, look in ITEM, look at ITEM1 in ITEM2";
}