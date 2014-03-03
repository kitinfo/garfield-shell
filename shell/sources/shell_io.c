#include "../headers/shell_io.h"
#include <stdio.h>

void read_line(char dest[]) {
    char buff[MAXLENGTH + 1];

    fgets(buff, MAXLENGTH, stdin);

    if (sscanf(buff, "%[^\n]", dest) != 1) {
		dest = "";
    }
}
