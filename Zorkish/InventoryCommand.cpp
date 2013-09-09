#include "InventoryCommand.h"
#include "Inventory.h"
#include "Health.h"
#include <sstream>

using namespace std;

string InventoryCommand::Execute(Player &player, const vector<string> *cmd) {
	Health *health = (Health*)player.GetComponent("HEALTH");
	Inventory *inventory = (Inventory*)player.GetComponent("INVENTORY");

	stringstream ss;
	ss << "Health: " << health->HealthLeft() << endl;
	ss << "Your inventory contains:" << endl << inventory->LongContents();
	return ss.str();
}