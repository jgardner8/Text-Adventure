#include "CommandProcessor.h"
#include <vector>
#include <set>
#include "Input.h"
#include "MoveCommand.h"

using namespace std;

CommandProcessor::CommandProcessor() {
	aCommand *move = new MoveCommand();
	_commands["MOVE"] = move;
	_commands["GO"] = move;
	_commands["N"] = move;
	_commands["S"] = move;
	_commands["W"] = move;
	_commands["E"] = move;
	_commands["U"] = move;
	_commands["D"] = move;
}

CommandProcessor::~CommandProcessor() {
	cout << "destroy";
	set<aCommand*> uniqueCmds;
	for (auto kvp : _commands)
		uniqueCmds.insert(kvp.second);
	for (auto cmd : uniqueCmds)
		delete cmd;
	cout << "complete";
}

string CommandProcessor::Process(Player &player, const string &input) {
	vector<string> *tokenised = Tokenize(input, " ");

	string result;
	bool foundCommand = _commands.find((*tokenised)[0]) != _commands.end();
	if (foundCommand) {
		string test = (*tokenised)[0];
		aCommand *cmd = _commands[test];
		result = cmd->Execute(player, tokenised);
	}
	else
		result = "Sorry, I don't know how to '" + input + "'";
	
	delete tokenised;
	return result;
}