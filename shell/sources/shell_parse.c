#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include "../headers/shell_sec.h"
#include "../headers/shell_debug.h"
#include "../headers/shell_help.h"

/**
 * @handsoff
 * parses Arguments
 */
void parseArguments(int argc, char* argv[]) {
    int c = -1;
    opterr = 0;
    while ((c = getopt(argc, argv, "u:p:h:d")) != -1) {

		switch (c) {
			case 'u':
			setUser(optarg);
			break;
			case 'p':
			setPassword(optarg);
			break;
			case 'h':
			printHelp();
			break;
			case 'd':
			setDebug(true);
			break;
			case '?':
			printf("Invalid arguments.\n");
			printHelp();
			break;
			default:
			return;
			break;
		}

    }

}
