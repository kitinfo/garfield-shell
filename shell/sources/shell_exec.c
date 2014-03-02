#include <unistd.h>
#include <stdio.h>


int popenAction(char* cmd, char* pw) {

	FILE* pipe = popen(cmd, "w");

	if (pipe == NULL) {
		return -1;
	}

	fprintf(pipe, pw);

	pclose(pipe);

	return 0;
}
