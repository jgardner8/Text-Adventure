#pragma once

#include "lib/tinyxml2.h"
#include <string>

class ZorkGame;
class Inventory;
class Item;

class ZorkGameFactory {
private:
	static void FillInventory(Inventory *inv, tinyxml2::XMLElement *invNode);
	static Item ItemFromXML(tinyxml2::XMLElement *itemNode);

public:
	static ZorkGame* FromFile(const std::string &worldName); //delete result
};

