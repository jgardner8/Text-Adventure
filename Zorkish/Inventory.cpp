#include "Inventory.h"
#include <algorithm>
#include <sstream>

using namespace std;

Inventory::Inventory() : aComponent("inventory") 
{ }

list<Item>::iterator Inventory::Find(const std::string &id) { 
	return find_if(begin(_items), end(_items), [id] (Item item) { return id == item.id(); } ); 
}

void Inventory::Add(const Item &item) {
	_items.push_back(item);
}

void Inventory::Remove(const string &id) { 
	_items.erase(Find(id));
}

bool Inventory::Contains(const string &id) { 
	return Find(id) != end(_items);
}

Item* Inventory::GetItem(const string &id) {
	auto it = Find(id);
	return it == end(_items) ? nullptr : &(*it);
}

std::string Inventory::Contents() {
	stringstream ss;
	for (Item item : _items) {
		ss << "\t" << item.id() << endl;
	}
	return ss.str();
} 