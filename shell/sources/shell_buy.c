#include "../headers/shell_exec.h"
#include "../headers/shell_cmd.h"
#include "../headers/shell_sec.h"
#include "../headers/shell_debug.h"
#include "../headers/shell_strings.h"
#include "../headers/shell_io.h"
#include "../headers/shell_find.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int execBuyWithName(char* snack, char* user, char* pass) {

	char* cwd = buildCmd(SNACKCMD, user);

	int len = strlen(cwd) + MAXLENGTH;

	char* cmd = malloc(len);
	snprintf(cmd, len,"%s %s -s %s", cwd, BUYCMD, snack);
        int status = popenAction(cmd, pass);
        free(cwd);
        free(cmd);

        return status;
}

int execBuyCmd(char* user, char* password, int id) {
	//do some magic
	char* cwd = buildCmd(SNACKCMD, user);
	int len = strlen(cwd) + MAXLENGTH;
	char* cmd = malloc(len);

	snprintf(cmd, len,"%s %s %d", cwd, BUYCMD, id);

	int status = popenAction(cmd, password);

	free(cwd);
	free(cmd);

	return status;
}

void execBuy(int id) {
    // buy
    printf("Buy snack with id: %d\n", id);
    execBuyCmd(getUser(), getPassword(), id);
}

int getSnackID(char* snack) {

    return findSnackByID(snack, getUser(), getPassword());
}

void buyMate() {

    int id = getSnackID(MATE);
    if (id < 0) {
		return;
    }
    debug("start buy with id");
    execBuy(id);
}

void buySnacks(char* input) {
    char* snacks;
    snacks = strtok(input, " ");
    int id = 0;
    while (snacks != NULL) {
		if (sscanf(snacks, "%d", &id) == 1) {
			execBuy(id);
		} else {
			execBuyWithName(snacks, getUser(), getPassword());
		}
		snacks = strtok(NULL, " ");
    }
}

void buy(char* input) {
    debug("init buy cmd");
    char dest[MAXLENGTH];
    if (begins(input, "snack ")) {
		sFirstCut(input, dest, 5);
		debug("exec buy snack");
		buySnacks(dest);
    } else if (begins(input, "mate")) {
		debug("exec buy mate");
		buyMate();
    } else {
		debug("no match in buy");
		printf("Don't know what you want...\n");
    }
}
