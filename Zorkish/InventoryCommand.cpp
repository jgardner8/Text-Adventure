#include "InventoryCommand.h"
#include "Inventory.h"

using namespace std;

string InventoryCommand::Execute(Player &player, const vector<string> *cmd) {
	Inventory *inventory = (Inventory*)player.GetComponent("INVENTORY");
	return "Your inventory contains:\n" + inventory->LongContents();
}