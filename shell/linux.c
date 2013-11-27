#include <stdio.h>
#include <stdlib.h>
#include "linux.h"
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

const char* SNACKCMD = "/garfield-snack";
const char* BUYCMD = "buy";
const char* VERBOSE = "--verbose";

int execBuyCmd(char* user, char* password, int id) {
	//do some magic
	char* cwd = getcwd(NULL, 0);

	char* cmd = malloc(strlen(cwd) + MAXLENGTH * 3);

	char* pwargs = "--pass";
	char* userargs = "--user";

	uint pid = snprintf(cmd, strlen(cwd) + MAXLENGTH *3,
		"%s%s %s %s %s %s %s %s %d",
		cwd,SNACKCMD, VERBOSE, userargs,
		user, pwargs, password, BUYCMD, id);
	printf(cmd);
	printf("\n");
	system(cmd);
	free(cwd);
	free(cmd);

	return pid;
}
