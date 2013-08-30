#pragma once

#include "aIdentifiable.h"
#include <string>

class Item : public aIdentifiable {
private:
	std::string _desc;

public:
	Item(std::string id, std::string description) : aIdentifiable(id) { 
		_desc = description; 
	}

	std::string desc() { return _desc; }
};

