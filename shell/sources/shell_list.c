#include "../headers/shell_strings.h"
#include "../headers/shell_sec.h"
#include <stdio.h>

void parseList(char* input) {

    /*char dest[MAXLENGTH];*/
    if (begins(input, "user")) {
		printf("user: ");
		printf("%s", getUser());
		printf("\n");
    }
}
