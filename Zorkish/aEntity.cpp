#include "aEntity.h"
#include <algorithm>

using namespace std;

vector<shared_ptr<aComponent>>::iterator aEntity::FindComponent(const string &id) {
	return find_if(begin(_components), end(_components), [id] (shared_ptr<aComponent> comp) { return id == comp.get()->id(); } ); 
}

void aEntity::AddComponent(aComponent *component) { 
	auto ptr = shared_ptr<aComponent>(component);
	_components.push_back(ptr);
}

void aEntity::RemoveComponent(const string &id) { 
	_components.erase(FindComponent(id));
}

bool aEntity::ContainsComponent(const string &id) {
	return FindComponent(id) != end(_components);
}

aComponent* aEntity::GetComponent(const string &id) { 
	auto it = FindComponent(id);
	return it == end(_components) ? nullptr : (*it).get();
}