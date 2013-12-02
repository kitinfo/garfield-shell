#pragma once
#define SNACKCMD "/../garfield-snack/garfield-snack"
#define USERCMD "/../garfield-user/garfield-user"
#define BUYCMD "buy"
#define FINDCMD "find"
#define LISTCMD "list"
#define USER_ARG "--user"
#define PORT_ARG "--port"
#define PASS_ARG "--pass"
#define VERBOSE "--verbose"

int execBuyCmd(char* user, char* password, int id);

int findSnack(char* snack, char* user, char* pass);

int findSnackByID(char* snack, char* user, char* pass);

char* getFindCmd(char* snack, char* user, char* pass);

char* buildCmd(char* cmd, char* user, char* pass);
