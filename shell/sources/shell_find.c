#include "../headers/shell_strings.h"
#include "../headers/shell_debug.h"
#include "../headers/shell_sec.h"
#include "../headers/shell_io.h"
#include "../headers/shell_exec.h"
#include "../headers/shell_cmd.h"
#include "../headers/shell_user.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int findSnack(char* snack) {

	char* cmd = getCmd(snack, SNACKCMD, FINDCMD);
	debug(cmd);

	int status = popenAction(cmd);

	free(cmd);

	return status;
}

void find(char* input) {

    char dest[MAXLENGTH];
    if (begins(input, "snack ")) {
		sFirstCut(input, dest, 6);
		debug("exec find snack cmd");
		findSnack(dest);
    } else if (begins(input, "user ")) {
    	sFirstCut(input, dest, 5);
    	debug("exec find user cmd");
    	findUser(dest);
    } else {
		debug("no match found in find");
		debug("try snack");
		findSnack(input);
    }
}
