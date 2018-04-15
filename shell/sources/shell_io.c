#include "../headers/shell_io.h"
#include <stdio.h>

int read_line(char dest[]) {
    char buff[MAXLENGTH + 1];

    if (fgets(buff, MAXLENGTH, stdin) == NULL) {
		return 0;
	}

    if (sscanf(buff, "%[^\n]", dest) != 1) {
		dest = "";
    }

	return 1;
}
