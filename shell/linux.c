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

	char* cmd = malloc(MAXLENGTH * 3 * sizeof(char));

	char* pwargs = "--user";
	char* userargs = "--user";

	snprintf(cmd, strlen(cwd) + MAXLENGTH *3,"%s%s %s %s %s %s %s %s %d", cwd,SNACKCMD, VERBOSE, userargs, user, pwargs, password, BUYCMD, id);

	uint pid = system(cmd);
	printf("pid: %d", pid);
}
