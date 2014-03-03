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

/**
 * parse the set command
 */
void parseSet(char* input) {
    
    char dest[MAXLENGTH];
    if (begins(input, "user ")) {
		sFirstCut(input, dest, 5);
		debug("set user");
		setUser(dest);
		return;
    } else if (begins(input, "pass ")) {
		sFirstCut(input, dest, 5);

		if (strlen(dest) < 1) {
			debug("ask for password");
			askPassword();
			return;
		}
		debug("set password");
		setPassword(dest);
		return;
    } else if (begins(input, "debug ")) {
    	sFirstCut(input, dest, 6);
    	if (begins(input, "true") || begins(input, "on")) {
    		setDebug(true);
    	} else if (begins(input, "false") || begins(input, "off")) {
    		setDebug(false);
    	}
    } else if (begins(input, "pgpass ")) {
    	sFirstCut(input, dest, 7);
    	if (begins(input, "true") || begins(input, "on")) {
    		setPGPass(true);
    	} else if (begins(input, "false") || begins(input, "off")) {
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

		char dest[MAXLENGTH];

		if (sequals(input, "exit")) {
			debug("shut down");
			return 0;
		} else if (begins(input, "set ")) {
			sFirstCut(input, dest, 4);
			debug("exec set cmd");
			parseSet(dest);
		} else if (begins(input, "list ")) {
			sFirstCut(input, dest, 5);
			debug("exec list cmd");
			parseList(dest);
		} else if (begins(input, "search ")) {
			sFirstCut(input, dest, 7);
			debug("exec find cmd from search");
			find(dest);
		} else if (begins(input, "find ")) {
			sFirstCut(input, dest, 5);
			debug("exec find cmd");
			find(dest);
		} else if (begins(input, "buy ")) {
			sFirstCut(input, dest, 4);
			debug("exec buy cmd");
			buy(dest);
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
