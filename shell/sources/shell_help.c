#include <stdio.h>
#include <stdlib.h>

void printHelp() {
    char* fn = "garfield-shell";
    printf("%s utility\n", fn);

    //options
    printf("Usage: %s [options] <mode> [mode-args]\n", fn);
    printf("Available options:\n");
    printf("\t-u | --user <user>\tGarfield user name\n");
    printf("\t-p | --pass <password>\tGarfield password\n");
    printf("\t-d | --debug\t\tPrint some debug info\n");
    printf("\t-g | --pgpass\t\tUse pgpass file\n");
    printf("\t-h | --help\t\tShow this help\n");

    //examples
    printf("\nExamples:\n");
    printf("%s -u test -p test\t\topens shell with user *test* and password *test*\n", fn);
    
    exit(EXIT_SUCCESS);
}

void printInternHelp() {
    printf("HELP:\n");
    printf("List of commands:\n");
    printf("\t set\n");
    printf("\t\t user <user>\t - sets the user\n");
    printf("\t\t password <pass> - sets the password,\n");
    printf("\t\t pgpass\n");
    printf("\t\t   <on|true>\t - use pgpass\n");
    printf("\t\t   <off|false>\t - don't use pgpass\n");
    printf("\t\t debug\n");
    printf("\t\t   <on|true>\t - show debugging info\n");
    printf("\t\t   <off|false>\t - don't show debugging info\n");
    printf("\t\t\t\t   ask if no argument\n");
    printf("\t list\n");
    printf("\t\t user <name>\t - search for user by name\n");
    printf("\t find\n");
    printf("\t\t user <select>\t - search a user in database\n");
    printf("\t\t snack <select>\t - search a snack in database\n");
    printf("\t buy\n");
    printf("\t\t snack <id>\t - buy a snack by id\n");
    printf("\t\t mate\t\t - buy a mate^^\n");

}
