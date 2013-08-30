#pragma once

#include <string>

class aIdentifiable {
private:
	std::string _id;

protected:
	aIdentifiable(std::string id) { _id = id; }

public:
	std::string id() { return _id; }
};