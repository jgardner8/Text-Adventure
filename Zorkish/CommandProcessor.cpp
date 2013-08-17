#include "CommandProcessor.h"
#include <vector>
#include <iostream>

using namespace std;

CommandProcessor::CommandProcessor() {
	//_commands["test"] = testCommand;
}

CommandProcessor::~CommandProcessor() {
	for (auto kvp : _commands)
		delete kvp.second;
}

//Adapted from: http://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
//DELETE RESULT
vector<string>* Tokenize(string input, string delimiter) {
	size_t pos = 0;
	auto tokens = new vector<string>();
	
	do {
		pos = input.find(delimiter);
	    tokens->push_back(input.substr(0, pos));
	    input.erase(0, pos + delimiter.length()); //"if the string is shorter, as many characters as possible are erased" -cplusplus.com
	} while (pos != string::npos);
	
	return tokens;
}

//Returns error, or "" on success
string CommandProcessor::Process(World &world, const string &input) {
	vector<string>* tokenised = Tokenize(input, " ");

	string error("");
	bool foundCommand = _commands.find((*tokenised)[0]) != _commands.end();
	if (foundCommand) 
		error = _commands[(*tokenised)[0]]->Execute(world, tokenised);
	
	delete tokenised;
	return error;
}