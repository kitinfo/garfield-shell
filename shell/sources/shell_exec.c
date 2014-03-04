#include "../headers/shell_sec.h"

#include <stdio.h>
#include <stdbool.h>

#ifdef _WIN32
	#define popen _popen
	#define pclose _pclose
#else
	#include <unistd.h>
#endif

int popenAction(char* cmd) {

	FILE* pipe = popen(cmd, "w");

	if (pipe == NULL) {
		return -1;
	}
	if (!getPGPass()) {
		fprintf(pipe, getPassword());
	}

	pclose(pipe);

	return 0;
}
