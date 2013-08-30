#pragma once

#include "aComponent.h"
#include <vector>

class Entity {
private:
	std::vector<aComponent> _components;

	std::vector<aComponent>::iterator FindComponent(const std::string &id); //returns end(vector) when not found

public:
	void AddComponent(const aComponent &component);
	void RemoveComponent(const std::string &id);
	bool ContainsComponent(const std::string &id);
	aComponent* GetComponent(const std::string &id);
};