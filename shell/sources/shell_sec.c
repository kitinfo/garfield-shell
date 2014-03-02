#include "../../garfield-common/getchar.h"
#include "../headers/shell_io.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * for saving user and password
 */
struct {
    char* user;
    char* password;
} login;


void initSec() {
	// get memory for password and user
    login.user = malloc(MAXLENGTH * sizeof (char));
    login.password = malloc(MAXLENGTH * sizeof (char));
}

void setUser(char* username) {
    strcpy(login.user, username);
}

void setPassword(char* pass) {
    strcpy(login.password, pass);
}

void askPassword() {
    char c;
    int i = 0;
    do {
		c = getch();
		if (c == 3) {
			//handle sigint during input
			return;
		}
		if (c != '\n' && c != '\r' && c != EOF) {
			//printf("%c|%x\n",c,c);
			login.password[i] = c;
		} else {
			break;
		}
		i++;
    } while (i < MAXLENGTH);
    login.password[i] = 0;
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

char* getPassword() {
	return login.password;
}

char* getUser() {
	return login.user;
}
