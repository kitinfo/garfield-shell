#include "../../garfield-common/getchar.h"
#include "../headers/shell_io.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * for saving user and password
 */
struct {
    char* user;
    char* password;
} login;

bool pgpass = false;

void freeSec() {
    free(login.user);
    free(login.password);
}

void initSec() {
    // get memory for password and user
    login.user = calloc(sizeof(char),MAXLENGTH);
    login.password = calloc(sizeof(char), MAXLENGTH);
}

void setUser(char* username) {
    strncpy(login.user, username, MAXLENGTH);
}

void setPassword(char* pass) {
    strncpy(login.password, pass, MAXLENGTH);
}

void setPGPass(bool flag) {
    pgpass = flag;
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

int checkLogin() {

    if (login.user == NULL || strlen(login.user) < 1) {
        printf("We need a user: ");
        char dest[MAXLENGTH];
        if (!read_line(dest)) {
			return 0;
		}
        setUser(dest);
    }
    if (!pgpass) {
        if (login.password == NULL || strlen(login.password) < 1) {
            printf("We need a password: ");
            askPassword();
            printf("\n");
        }
    }

	return 1;
}

char* getPassword() {
    return login.password;
}

char* getUser() {
    return login.user;
}

bool getPGPass() {
    return pgpass;
}


