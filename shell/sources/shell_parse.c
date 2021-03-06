#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../headers/shell_sec.h"
#include "../headers/shell_debug.h"
#include "../headers/shell_help.h"

void parseArguments(int argc, char* argv[]) {

    //parse arguments
    int i;
    for (i = 1; i < argc; i++) {
        if (*argv[i] == '-') {
            if (i + 1 < argc && (!strcmp(argv[i], "--user") || !strcmp(argv[i], "-u"))) {
                setUser(argv[i + 1]);
                i++;
            }  else if (i + 1 < argc && (!strcmp(argv[i], "--pass") || !strcmp(argv[i], "-p"))) {
                setPassword(argv[i + 1]);
                i++;
            }  else if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
                printHelp();
            } else if (!strcmp(argv[i], "--debug") || !strcmp(argv[i], "-d")) {
                setDebug(true);
            } else if (!strcmp(argv[i], "--pgpass") || !strcmp(argv[i], "-g")) {
                setPGPass(true);
            } else {
                printf("Invalid arguments.\n");
                printHelp();
            }
        }
    }
}
