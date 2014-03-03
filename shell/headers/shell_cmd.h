#pragma once

#define FINDCMD "find"
#define BUYCMD "buy"
#define SNACKCMD "garfield-snack"
#define USER_ARG "--user"
#define USERCMD "garfield-user"
#define LISTCMD "list"
#define MATE "4029764001807"

char* buildCmd(char* garfieldCmd);

char* getCmd(char* tag, char* progCmd, char* searchCmd);
