#pragma once

#include "aIdentifiable.h"
#include <string>

class aComponent : public aIdentifiable {
protected:
	aComponent(std::string id) : aIdentifiable(id) {}
};