#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "garfield.h"
#include "helper.h"
#include "getchar.h"


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

char* askPassword() {

	char* password = malloc(MAXLENGTH);

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
                                password[i]=c;
                        }
                        else{
                                break;
                        }
                        i++;
                }
                while(i<MAXLENGTH);
                password[i]=0;

		return password;
}

bool begins(char* longer, char* shorter) {

        int len = strlen(shorter);
        char dest[len +1];

        strncpy(dest, &longer[0], len);
        dest[len] = '\0';

        return sequals(dest, shorter);
}

bool sequals(char* one, char* two) {

        if (strlen(one) < 1 || strlen(two) < 1 || strlen(one) != strlen(two)) {
                return false;
        }

        if (strcmp(one, two) == 0) {
                return true;
        }
        return false;
}
