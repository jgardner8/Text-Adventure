#pragma once

#include "aComponent.h"
#include <vector>

class aEntity {
private:
	std::vector<aComponent*> _components; //stored as pointer for polymorphism

	std::vector<aComponent*>::iterator FindComponent(const std::string &id); //returns end(vector) when not found

protected:
	~aEntity();

public:
	void AddComponent(aComponent *component); //must be allocated by you. aEntity takes ownership. 
	void RemoveComponent(const std::string &id);
	bool ContainsComponent(const std::string &id);
	aComponent* GetComponent(const std::string &id);
};