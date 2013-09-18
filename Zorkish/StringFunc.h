#pragma once

#include <string>

inline std::string ToUpper(std::string str) {
	for (char &c : str) 
		c = toupper(c);
	return str;
}