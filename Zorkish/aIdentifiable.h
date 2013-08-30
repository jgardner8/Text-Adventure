#pragma once

#include <string>

class aIdentifiable {
private:
	std::string _id;

protected:
	//All ids are transformed to upper-case
	aIdentifiable(const std::string &id) { 
		_id = id;
		for (char &c : _id) 
			c = toupper(c);
	}

public:
	std::string id() { return _id; }
};