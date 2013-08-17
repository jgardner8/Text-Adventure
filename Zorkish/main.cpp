#include "CommandProcessor.h"

int main() {
	CommandProcessor cmdProc;
	cmdProc.Process("test");
	cmdProc.Process("test string 1 2 3");
	cmdProc.Process("");

	return 0;
}