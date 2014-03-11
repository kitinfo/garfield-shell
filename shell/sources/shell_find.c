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

    if (begins(input, "snack ")) {
		debug("exec find snack cmd");
		findSnack(input + 6);
    } else if (begins(input, "user ")) {
    	debug("exec find user cmd");
    	findUser(input + 5);
    } else {
		debug("no match found in find");
		debug("try snack");
		findSnack(input);
    }
}
