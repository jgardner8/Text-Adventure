#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "StringFunc.h"

//All input is always in uppercase
namespace { //removes need for .cpp file
	void FlushCin() {
		//http://stackoverflow.com/questions/257091/how-do-i-flush-the-cin-buffer
		std::cin.clear(); //reset state
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //flush
	}

	char GetInputBlocking() {
		char input;
		std::cin >> input;
		FlushCin();
		return toupper(input);
	}
	
	std::string GetInputStrBlocking() {
		std::string input;
		getline(std::cin, input);
		return ToUpper(input);
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
