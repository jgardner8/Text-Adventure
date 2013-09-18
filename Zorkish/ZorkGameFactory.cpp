#include "ZorkGameFactory.h"
#include <iostream>
#include <stdexcept>
#include "Health.h"
#include "Trap.h"
#include "Inventory.h"
#include "ZorkGame.h"
#include "Room.h"

using namespace std;
using namespace tinyxml2;

//Fills an Inventory component, given an Inventory XMLElement
void ZorkGameFactory::FillInventory(Inventory *inv, XMLElement *invNode) {
	if (!inv || !invNode)
		return;
	auto itemNode = invNode->FirstChildElement("Item");
	do {
		inv->Add(ItemFromXML(itemNode));
	} while (itemNode = itemNode->NextSiblingElement());
}

//Creates an item, and if it has an inventory component, parses it using FillInventory.
//FillInventory will in turn request more items be created, calling this function, so
//the implementation works for arbitrary levels of nesting.
Item ZorkGameFactory::ItemFromXML(XMLElement *itemNode) {
	Item item(itemNode->Attribute("name"), itemNode->Attribute("desc"));
	if (auto invNode = itemNode->FirstChildElement("Inventory")) {
		auto inv = new Inventory();
		FillInventory(inv, invNode);
		item.AddComponent(inv);
	}
	return item;
}

//Creates a ZorkGame from a world XML file.
//See worlds/test.xml for an example.
ZorkGame* ZorkGameFactory::FromFile(const string &worldName) {
	//Open file
	string filename = "worlds/" + worldName + ".xml";
	XMLDocument file;
	file.LoadFile(filename.c_str());
	if (file.Error())
		throw exception(("Error occurred while loading file: " + filename).c_str());

	//Create world from file
	auto *world = new ZorkGame();
	unordered_map<string, int> roomIds; //roomId to _map idx map for connecting rooms
	int playerRoomIdx = -1;
	Room *room;
	auto *roomNode = file.FirstChild()->FirstChildElement();
	//For each room
	do {
		//Create room
		world->_map.push_back(Room(roomNode->Attribute("desc")));
		room = &world->_map[world->_map.size()-1]; //alias
		if (auto id = roomNode->Attribute("id"))
			roomIds[id] = world->_map.size()-1; //for connections
		FillInventory(
			(Inventory*)room->GetComponent("INVENTORY"),
			roomNode->FirstChildElement("Inventory"));
		
		//Add traps (not implemented past a simple demo)
		if (auto trapNode = roomNode->FirstChildElement("Trap")) {
			if (int damage = trapNode->IntAttribute("damage")) {
				bool keyNeeded;
				if (!trapNode->QueryBoolAttribute("keyNeeded", &keyNeeded)) {
					room->AddTrap(new Trap(room, damage, keyNeeded));
				}
			}
		}

		//Create connections (if applicable)
		if (auto connectNode = roomNode->FirstChildElement("ConnectTo")) {
			if (!room->ConnectTo(
					&world->_map[roomIds[connectNode->Attribute("id")]],
					connectNode->Attribute("direction"))) {
				throw exception(("Could not connect rooms in world: " + worldName).c_str());
			}
		}
			
		//Create player (if applicable)
		if (auto playerNode = roomNode->FirstChildElement("Player")) {
			playerRoomIdx = world->_map.size()-1; 
			FillInventory( 
				(Inventory*)world->_player.GetComponent("INVENTORY"), 
				playerNode->FirstChildElement("Inventory"));
			
			//Set start health
			if (int specifiedHealth = playerNode->IntAttribute("health")) //returns 0 on error
			{
				Health *health = (Health*)world->_player.GetComponent("HEALTH");
				health->Hurt(health->HealthLeft() - specifiedHealth);
			}
		}
	} while (roomNode = roomNode->NextSiblingElement());

	//Set player location
	if (playerRoomIdx == -1)
		throw exception(("No Player defined in world: " + worldName).c_str());
	world->_player.location(&world->_map[playerRoomIdx]);

	return world;
}