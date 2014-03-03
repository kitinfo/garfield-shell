#include "../headers/shell_parse.h"
#include "../headers/shell_shell.h"
#include "../headers/shell_sec.h"

/**
 * garfield-shell
 */
int main(int argc, char* argv[]) {

	// get memory for login data
    initSec();

	// if we have arguments
    if (argc > 0) {
		parseArguments(argc, argv);
    }

    return shell();
}
