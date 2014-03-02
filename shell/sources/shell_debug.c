#include <stdio.h>
#include <stdbool.h>

bool debugFlag = false;

// if debugFlag is true print a message
void debug(char* message) {
    if (debugFlag) {
	printf("debug: %s\n", message);
    }
}

// sets the debug flag
void setDebug(bool flag) {
	debugFlag = flag;
}
