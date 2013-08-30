#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

//All input is always in uppercase
namespace { //removes need for .cpp file
	char GetInputBlocking() {
		char input;
		std::cin >> input;
		return toupper(input);
	}
	
	std::string GetInputStrBlocking() {
		std::string input;
		std::cin >> input;
		for (char &c : input) c = toupper(c);
		return input;
	}
	
	//DELETE RESULT
	std::vector<std::string>* Tokenize(std::string input, std::string delimiter) {
		size_t pos = 0;
		auto tokens = new std::vector<std::string>();
		
		do {
			pos = input.find(delimiter);
		    tokens->push_back(input.substr(0, pos));
		    input.erase(0, pos + delimiter.length()); //"if the string is shorter, as many characters as possible are erased" -cplusplus.com
		} while (pos != std::string::npos);
		
		return tokens;
	}
}
