#include "CommandProcessor.h"
#include <vector>
#include <set>
#include "Input.h"

using namespace std;

CommandProcessor::CommandProcessor() {
	//_commands["test"] = testCommand;
}

CommandProcessor::~CommandProcessor() {
	set<aCommand*> commands; //avoid deleting same command twice
	for (auto kvp : _commands)
		commands.insert(kvp.second);
	for (auto cmd : commands)
		delete cmd;
}

string CommandProcessor::Process(Player &player, const string &input) {
	vector<string>* tokenised = Tokenize(input, " ");

	string error = "";
	bool foundCommand = _commands.find((*tokenised)[0]) != _commands.end();
	if (foundCommand) 
		error = _commands[(*tokenised)[0]]->Execute(player, tokenised);
	
	delete tokenised;
	return error;
}