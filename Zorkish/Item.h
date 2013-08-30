#pragma once

#include "aIdentifiable.h"
#include "aEntity.h"
#include <string>
#include <sstream>

class Item : public aIdentifiable, public aEntity {
private:
	std::string _desc;

public:
	Item(std::string id, std::string description) : aIdentifiable(id) { _desc = description; }

	std::string desc() { return _desc; }
	std::string longDesc() { 
		std::stringstream ss;
		ss << "(" << id() << ") " << _desc;
		return ss.str();
	}
};

