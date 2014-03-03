#include <stdio.h>
#include <stdlib.h>

void printHelp() {
    char* fn = "garfield-shell";
    printf("%s utility\n", fn);

    //options
    printf("Usage: %s [options] <mode> [mode-args]\n", fn);
    printf("Available options:\n");
    printf("\t-u <user>\tDatabase user name\n");
    printf("\t-p <password>\tDatabase password\n");
    printf("\t-d\t\tPrint some debug info\n");

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
    printf("\t\t password <pass>\t - sets the password,\n");
    printf("\t\t\t\t ask if no argument\n");
    printf("\t list\n");
    printf("\t\t user <select>\t - prints all user,\n");
    printf("\t\t\t\t if we have a select, search\n");
    printf("\t find\n");
    printf("\t\t user <select>\t - search a user in database\n");
    printf("\t\t snack <select>\t - search a snack in database\n");
    printf("\t buy\n");
    printf("\t\t snack <select>\t - buy a snack,\n");
    printf("\t\t\t\t select is the snack id (find it with search)\n");
    printf("\t\t mate\t\t - buy a mate^^\n");

}
