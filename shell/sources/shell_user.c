#include "../headers/shell_cmd.h"
#include "../headers/shell_exec.h"
#include "../headers/shell_debug.h"
#include <stdlib.h>

int findUser(char* search, char* loginUser, char* pass) {

	char* cmd = getUserCmd(search, loginUser);
	debug(cmd);

	int status = popenAction(cmd, pass);

	free(cmd);

	return status;
}
