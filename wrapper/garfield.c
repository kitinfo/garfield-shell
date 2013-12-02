#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "helper.h"
#include "garfield.h"

int main (int argc, char* argv[]) {

	char* cmd;

	printf("Garfield shell wrapper %s\n", VERSION);
	printf(argv[1]);
	printf("\n");

	if (argc < 2) {
		printHelp();
		return -1;
	}

	if (sequals(argv[1], "user")) {
		cmd = USERCMD;
	} else if (sequals(argv[1], "snack")) {
		cmd = SNACKCMD;
	} else if (sequals(argv[1], "help")) {
		printHelp();
		return 0;
	}
	if (cmd == NULL) {
		printf("Need arguments.\n");
		printHelp();
		return -2;
	}

	char** ptr = &argv[2];

	return execv(cmd, ptr);
}


void printHelp() {

	printf("Commands: \n");
	printf("\t garfield user <args>\t - for user actions\n");
	printf("\t garfield snack <args>\t - for snack actions\n");
}
