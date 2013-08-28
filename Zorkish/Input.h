#pragma once

#include <iostream>

static char GetInputBlocking() {
	char input;
	std::cin >> input;
	return toupper(input);
}