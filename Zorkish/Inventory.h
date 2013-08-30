#pragma once

#include "aComponent.h"
#include "Item.h"
#include <list>

class Inventory : public aComponent {
private:
	std::list<Item> _items;

	std::list<Item>::iterator Find(const std::string &id);

public:
	Inventory();
	~Inventory();

	void Add(const Item &item);
	void Remove(const std::string &id);
	bool Contains(const std::string &id);
	Item* GetItem(const std::string &id);
	std::string Contents();
};

