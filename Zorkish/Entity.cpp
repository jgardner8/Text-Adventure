#include "Entity.h"
#include <algorithm>

using namespace std;

vector<aComponent>::iterator Entity::FindComponent(const string &id) {
	return find_if(begin(_components), end(_components), [id] (aComponent comp) { return id == comp.id(); } ); 
}

void Entity::AddComponent(const aComponent &component) { 
	_components.push_back(component);
}

void Entity::RemoveComponent(const string &id) { 
	_components.erase(FindComponent(id));
}

bool Entity::ContainsComponent(const string &id) {
	return FindComponent(id) != end(_components);
}

aComponent* Entity::GetComponent(const string &id) { 
	auto it = FindComponent(id);
	return it == end(_components) ? nullptr : &(*it);
}