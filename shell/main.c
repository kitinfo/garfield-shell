#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include "../garfield-common/getchar.h"
#include "main.h"
#include "linux.h"

struct {
	char* user;
	char* password;
}login;


/**
 * garfield-shell
 */
int main(int argc, char* argv[]) {

	login.user = malloc(MAXLENGTH * sizeof(char));
	login.password = malloc(MAXLENGTH * sizeof(char));

	if (argc > 0) {
		parseArguments(argc, argv);
	}

	return shell();
}

/**
 * @handsoff
 * parses Arguments
 */
void parseArguments(int argc, char* argv[]) {
	int c = -1;
	opterr = 0;
	while ((c = getopt (argc, argv, "u:p:h")) != -1) {

		switch(c) {
			case 'u':
				setUser(optarg);
			break;
			case 'p':
				setPassword(optarg);
			break;
			case 'h':
				printHelp();
			break;
			case '?':
				printf("Invalid arguments.\n");
				printHelp();
			break;
			default:
				return;
			break;
		}

	}

}

void printHelp() {




	exit(EXIT_SUCCESS);
}

/**
 * shell function.
 *
 */
int shell() {

	checkLogin();

	char input[MAXLENGTH];
	for (;;) {
		printf("%s>", login.user);

		read_line(input);

		char dest[MAXLENGTH];

		if (sequals(input, "exit")) {
			return 0;
		} else if (begins(input, "set ")) {
			sFirstCut(input, dest, 4);
			parseSet(dest);
		} else if (begins(input, "list ")) {
			sFirstCut(input, dest, 5);
			parseList(dest);
		} else if (begins(input, "search ")) {
                	sFirstCut(input, dest, 7);
			find(dest);
        	} else if (begins(input, "find ")) {
                	sFirstCut(input, dest, 5);
			find(dest);
        	} else if (begins(input, "buy ")) {
                	sFirstCut(input, dest, 4);
			buy(dest);
        	} else if (begins(input, "help")) {
			printInternHelp();
		} else {
			printf("Don't know what you mean...\n");
		}

	}

	return 0;
}

void find(char* input) {

	char dest[MAXLENGTH];

	if (begins(input, "snack ")) {
		sFirstCut(input, dest, 6);
		findSnack(dest, login.user, login.password);
	}
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





/**
 * @handsoff
 *deletes the first <len> chars from input and writes the rest
 * to dest.
 */
void sFirstCut(char* input, char* dest, int len) {
	if (strlen(input) > len) {
		char* dest0 = input + len;
		// dont forget to copy string
		strcpy(dest, dest0);
		return;
	} else {
		dest = "";
	}
}

/**
 * parse the set command
 */
void parseSet(char* input) {

	char dest[MAXLENGTH];
	if (begins(input, "user ")) {
		sFirstCut(input, dest, 5);
		setUser(dest);
		return;
	} else if (begins(input, "pass ")) {
		sFirstCut(input, dest, 5);

		if (strlen(dest) < 1) {
			askPassword();
			return;
		}
		setPassword(dest);
		return;
	}

	printf("Don't know what you want...\n");
}


void buy(char* input) {
	char dest[MAXLENGTH];
	if (begins(input, "snack ")) {
		sFirstCut(input, dest, 5);
		buySnacks(dest);
	} else if (begins(input, "mate")) {
		buyMate();
	}
}

void checkLogin() {
	if (strlen(login.user) < 1) {
                printf("We need a user: ");
                char dest[MAXLENGTH];
                read_line(dest);
                setUser(dest);
        }
        if (strlen(login.password) < 1) {
                printf("We need a password: ");
                askPassword();
        }

}


void buySnacks(char* input) {
	char* snacks;/* = malloc(MAXLENGTH * sizeof(char));*/
	snacks = strtok(input, " ");
	int id = 0;
	while (snacks != NULL) {
		if (sscanf(snacks,"%d", &id) == 1) {
			execBuy(id);
		} else {
			execBuyWithName(snacks, login.user, login.password);
		}
		snacks = strtok(NULL, " ");
	}
}

int getSnackID(char* snack) {

	return findSnackByID(snack, login.user, login.password);
}


void buyMate() {

	int id = getSnackID(MATE);
	if (id < 0) {
		return;
	}
	execBuy(id);
}

void execBuy(int id) {
	// buy
	printf("Buy snack with id: %d\n", id);
	execBuyCmd(login.user, login.password, id);
}


void askPassword() {
	char c;
	int i=0;
                do{
                        c=getch();
                        if(c==3){
                                //handle sigint during input
                                return;
                        }
                        if(c!='\n'&&c!='\r'&&c!=EOF){
                                //printf("%c|%x\n",c,c);
                                login.password[i]=c;
                        }
                        else{
                                break;
                        }
                        i++;
                }
                while(i<MAXLENGTH);
                login.password[i]=0;
}



void parseList(char* input) {

	/*char dest[MAXLENGTH];*/
	if (begins(input, "user")) {
		printf("user: ");
		printf(login.user);
		printf("\n");
	}
}


void setUser(char* username) {
	strcpy(login.user, username);
}

void setPassword(char* pass) {
	strcpy(login.password, pass);
}


bool begins(char* longer, char* shorter) {

	int len = strlen(shorter);
	char dest[len +1];

	strncpy(dest, &longer[0], len);
	dest[len] = '\0';

	return sequals(dest, shorter);
}




void read_line(char dest[]) {
	char buff[MAXLENGTH + 1];

	fgets(buff, MAXLENGTH, stdin);

	if (sscanf(buff, "%[^\n]", dest) != 1) {
		dest = "";
	}
}



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
