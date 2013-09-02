#pragma once

#include "ZorkGame.h"
#include "Inventory.h"
#include "lib/tinyxml2.h"

class ZorkGameFactory {
private:
	static void FillInventory(Inventory *inv, tinyxml2::XMLElement *invNode);
	static Item ItemFromXML(tinyxml2::XMLElement *itemNode);

public:
	static ZorkGame* FromFile(const std::string &worldName); //delete result
};

