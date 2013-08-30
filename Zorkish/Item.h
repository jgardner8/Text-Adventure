#pragma once

#include "aIdentifiable.h"
#include "aEntity.h"
#include <string>

class Item : public aIdentifiable, public aEntity {
private:
	std::string _desc;

public:
	Item(std::string id, std::string description) : aIdentifiable(id) { 
		_desc = description; 
	}

	std::string desc() { return _desc; }
};

