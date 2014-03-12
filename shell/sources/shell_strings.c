#include <string.h>
#include <stdbool.h>

bool sequals(char* one, char* two) {

    if (strlen(one) < 1 || strlen(two) < 1 || strlen(one) !=
	    strlen(two)) {
	return false;
    }

    if (strcmp(one, two) == 0) {
	return true;
    }
    return false;
}

bool begins(char* longer, char* shorter) {

    int len = strlen(shorter);
    char dest[len + 1];

    strncpy(dest, &longer[0], len);
    dest[len] = '\0';

    return sequals(dest, shorter);
}
