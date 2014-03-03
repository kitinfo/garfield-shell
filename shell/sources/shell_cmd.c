#include "../headers/shell_cmd.h"
#include "../headers/shell_io.h"
#include "../headers/shell_sec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char* buildCmd(char* garfieldCmd) {

	int len = MAXLENGTH;
	char* cmd = malloc(len);

	if (getPGPass()) {
		snprintf(cmd, len, "%s %s %s \"%s\"", garfieldCmd, PGPASS_ARG, USER_ARG, getUser());
	} else {
		snprintf(cmd, len, "%s %s \"%s\"", garfieldCmd, USER_ARG, getUser());
	}
	
	return cmd;
}

char* getCmd(char* tag, char* progCmd, char* searchCmd) {

	char* cwd = buildCmd(progCmd);
	int len = strlen(cwd) + MAXLENGTH;
	char* cmd = malloc(len);

    snprintf(cmd, len, "%s %s \"%s\"", cwd, searchCmd, tag);
	free(cwd);
	return cmd;
}
