#include "../headers/shell_sec.h"
#include <unistd.h>
#include <stdio.h>


int popenAction(char* cmd) {

	FILE* pipe = popen(cmd, "w");

	if (pipe == NULL) {
		return -1;
	}

	fprintf(pipe, getPassword());

	pclose(pipe);

	return 0;
}
