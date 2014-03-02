#include "../headers/shell_cmd.h"
#include "../headers/shell_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* buildCmd(char* garfieldCmd, char* user) {

	int len = MAXLENGTH;
	char* cmd = malloc(len);

	snprintf(cmd, len, "%s %s \"%s\"",
		garfieldCmd, USER_ARG, user);
	return cmd;
}

char* getFindCmd(char* snack, char* user) {

	char* cwd = buildCmd(SNACKCMD,user);
        int len = strlen(cwd) + MAXLENGTH;
        char* cmd = malloc(len);

        snprintf(cmd, len, "%s %s \"%s\"", cwd, FINDCMD, snack);
	free(cwd);
	return cmd;
}
