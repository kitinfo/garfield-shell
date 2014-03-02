#include "../headers/shell_strings.h"
#include "../headers/shell_debug.h"
#include "../headers/shell_sec.h"
#include "../headers/shell_io.h"
#include "../headers/shell_exec.h"
#include "../headers/shell_cmd.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int findSnackByID(char* snack,char* user, char* pass) {
	//TODO: new implementation
	/*
	char* cmd = getFindCmd(snack, user);

	FILE* out = popen(cmd, "r");

	int id = -1;

	fscanf(out,"%d", &id);
	printf("id: %d\n",id);
	pclose(out);
	free(cmd);
	
	return id;
	*/
	return 0;
}

int findSnack(char* snack, char* user, char* pass) {

	char* cmd = getFindCmd(snack, user);
	debug(cmd);

	int status = popenAction(cmd, pass);

	free(cmd);

	return status;
}

void find(char* input) {

    char dest[MAXLENGTH];
    if (begins(input, "snack ")) {
		sFirstCut(input, dest, 6);
		debug("exec find snack cmd");
		findSnack(dest, getUser(), getPassword());
    } else {
		debug("no match found in find");
		debug("try snack");
		findSnack(input, getUser(), getPassword());
    }
}
