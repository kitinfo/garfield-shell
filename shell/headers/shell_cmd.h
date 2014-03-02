#pragma once

#define FINDCMD "find"
#define BUYCMD "buy"
#define SNACKCMD "garfield-snack"
#define USER_ARG "--user"
#define MATE "4029764001807"

char* buildCmd(char* garfieldCmd, char* user);

char* getFindCmd(char* snack, char* user);
