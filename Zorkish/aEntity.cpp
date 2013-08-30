#include "aEntity.h"
#include <algorithm>

using namespace std;

vector<aComponent>::iterator aEntity::FindComponent(const string &id) {
	return find_if(begin(_components), end(_components), [id] (aComponent comp) { return id == comp.id(); } ); 
}

void aEntity::AddComponent(const aComponent &component) { 
	_components.push_back(component);
}

void aEntity::RemoveComponent(const string &id) { 
	_components.erase(FindComponent(id));
}

bool aEntity::ContainsComponent(const string &id) {
	return FindComponent(id) != end(_components);
}

aComponent* aEntity::GetComponent(const string &id) { 
	auto it = FindComponent(id);
	return it == end(_components) ? nullptr : &(*it);
}