#pragma once

#include "aComponent.h"
#include <vector>
#include <memory>

class aEntity {
private:
	//Stored as pointer for polymorphism. 
	//The shared pointer fixes an issue I had where I couldn't define a proper 
	//copy constructor/assignment operator since I didn't know the real type of the components.
	std::vector<std::shared_ptr<aComponent>> _components; 

	std::vector<std::shared_ptr<aComponent>>::iterator FindComponent(const std::string &id); //returns end(vector) when not found

public:
	void AddComponent(aComponent *component); //your pointer is invalidated when the aEntity is destroyed
	void RemoveComponent(const std::string &id);
	bool ContainsComponent(const std::string &id);
	aComponent* GetComponent(const std::string &id);
};