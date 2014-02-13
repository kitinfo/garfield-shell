#include <stdio.h>
#include <stdlib.h>
#include "linux.h"
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"

int execBuyCmd(char* user, char* password, int id) {
	//do some magic
	char* cwd = buildCmd(SNACKCMD, user, password);
	int len = strlen(cwd) + MAXLENGTH;
	char* cmd = malloc(len);

	snprintf(cmd, len,"%s %s %d", cwd, BUYCMD, id);
	uint pid = system(cmd);
	free(cwd);
	free(cmd);

	return pid;
}

char* buildCmd(char* garfieldCmd, char* user, char* pass) {
	//char* cwd = ""; //getcwd(NULL, 0);
	int len = MAXLENGTH * 3; //strlen(cwd) + MAXLENGTH * 3;
	char* cmd = malloc(len);

	snprintf(cmd, len, "%s %s \"%s\" %s \"%s\"",
		garfieldCmd, USER_ARG, user, PASS_ARG, pass);
	//free(cwd);
	return cmd;
}



int findSnackByID(char* snack,char* user, char* pass) {

	char* cmd = getFindCmd(snack, user, pass);

	FILE* out = popen(cmd, "r");

	int id = -1;

	fscanf(out,"%d", &id);
	printf("id: %d\n",id);
	pclose(out);
	free(cmd);

	return id;
}

int findSnack(char* snack, char* user, char* pass) {

	char* cmd = getFindCmd(snack, user, pass);
	int pid = system(cmd);
	free(cmd);

	return pid;
}

char* getFindCmd(char* snack, char* user, char* pass) {

	char* cwd = buildCmd(SNACKCMD,user, pass);
        int len = strlen(cwd) + MAXLENGTH;
        char* cmd = malloc(len);

        snprintf(cmd, len, "%s %s \"%s\"", cwd, FINDCMD, snack);
	free(cwd);
	return cmd;
}

void listUserCmd(char* user, char* pass, char* searchCmd) {

	char* cwd = buildCmd(USERCMD, user, pass);

	int len = strlen(cwd) + MAXLENGTH;

	char* cmd = malloc(len);

	if (searchCmd != NULL) {
	snprintf(cmd, len, "%s %s \"%s\"", cwd, LISTCMD, searchCmd);
	} else {
		snprintf(cmd, len, "%s %s", cwd, LISTCMD);
	}
	system(cmd);
	free(cwd);
}

int execBuyWithName(char* snack, char* user, char* pass) {

	char* cwd = buildCmd(SNACKCMD, user, pass);

	int len = strlen(cwd) + MAXLENGTH;

	char* cmd = malloc(len);
	snprintf(cmd, len,"%s %s -s %s", cwd, BUYCMD, snack);
        uint pid = system(cmd);
        free(cwd);
        free(cmd);

        return pid;
}
