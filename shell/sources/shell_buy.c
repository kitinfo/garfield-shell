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

int execBuyWithName(char* snack) {

	char* cwd = buildCmd(SNACKCMD);

	int len = strlen(cwd) + MAXLENGTH;

	char* cmd = malloc(len);
	snprintf(cmd, len,"%s %s -s %s", cwd, BUYCMD, snack);
        int status = popenAction(cmd);
        free(cwd);
        free(cmd);

        return status;
}

int execBuy(int id) {
    printf("Buy snack with id: %d\n", id);
    //do some magic
	char* cwd = buildCmd(SNACKCMD);
	int len = strlen(cwd) + MAXLENGTH;
	char* cmd = malloc(len);

	snprintf(cmd, len,"%s %s %d", cwd, BUYCMD, id);

	int status = popenAction(cmd);

	free(cwd);
	free(cmd);

	return status;
}

void buySnacks(char* input) {
    char* snacks;
    snacks = strtok(input, " ");
    int id = 0;
    while (snacks != NULL) {
		if (sscanf(snacks, "%d", &id) == 1) {
			execBuy(id);
		} else {
			execBuyWithName(snacks);
		}
		snacks = strtok(NULL, " ");
    }
}

void buy(char* input) {
    debug("init buy cmd");
    if (begins(input, "snack ")) {
		debug("exec buy snack");
		buySnacks(input + 5);
    } else if (begins(input, "mate")) {
		debug("exec buy mate");
		execBuyWithName(MATE);
    } else {
		debug("no match in buy");
		printf("Don't know what you want...\n");
    }
}
