#include "../headers/shell_strings.h"
#include "../headers/shell_debug.h"
#include "../headers/shell_help.h"
#include "../headers/shell_io.h"
#include "../headers/shell_find.h"
#include "../headers/shell_buy.h"
#include "../headers/shell_list.h"
#include "../headers/shell_sec.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void shellExit() {
    
    freeSec();
    exit(EXIT_SUCCESS);
}

/**
 * parse the set command
 */
void parseSet(char* input) {
    printf("%s\n", input);
    if (begins(input, "user ")) {
		debug("set user");
		setUser(input + 5);
		return;
    } else if (begins(input, "pass ")) {

		if (strlen(input + 5) < 1) {
			debug("ask for password");
			askPassword();
			return;
		}
		debug("set password");
		setPassword(input + 5);
		return;
    } else if (begins(input, "debug ")) {
    	if (begins(input + 6, "true") || begins(input +6, "on")) {
    		setDebug(true);
    	} else if (begins(input + 6, "false") || begins(input + 6, "off")) {
    		setDebug(false);
    	}
    } else if (begins(input, "pgpass ")) {
        
    	if (begins(input + 7, "true") || begins(input + 7, "on")) {
    		setPGPass(true);
    	} else if (begins(input + 7, "false") || begins(input + 7, "off")) {
    		setPGPass(false);
    	}
    }
    debug("no match in set");
    printf("Don't know what you want...\n");
}


/**
 * shell function
 */
int shell() {

    debug("shell init");
    checkLogin();

    char input[MAXLENGTH];
    for (;;) {
		printf("%s>", getUser());

		read_line(input);

		if (sequals(input, "exit")) {
			debug("shut down");
			shellExit();
		} else if (begins(input, "set ")) {
			debug("exec set cmd");
			parseSet(input + 4);
		} else if (begins(input, "list ")) {
			debug("exec list cmd");
			parseList(input + 5);
		} else if (begins(input, "search ")) {
			debug("exec find cmd from search");
			find(input + 7);
		} else if (begins(input, "find ")) {
			debug("exec find cmd");
			find(input + 5);
		} else if (begins(input, "buy ")) {
			debug("exec buy cmd");
			buy(input + 4);
		} else if (begins(input, "help")) {
			debug("exec help cmd");
			printInternHelp();
		} else {
			debug("no match found in shell");
			printf("Don't know what you mean...\n");
		}
    }
    return 0;
}
