#include "../headers/shell_cmd.h"
#include "../headers/shell_exec.h"
#include "../headers/shell_debug.h"
#include <stdlib.h>

int findUser(char* search) {

	char* cmd = getCmd(search, USERCMD, LISTCMD);
	debug(cmd);

	int status = popenAction(cmd);

	free(cmd);

	return status;
}
