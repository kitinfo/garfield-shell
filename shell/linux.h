#pragma once

int execBuyCmd(char* user, char* password, int id);

int findSnack(char* snack, char* user, char* pass);

int findSnackByID(char* snack, char* user, char* pass);

char* getFindCmd(char* snack, char* user, char* pass);

char* buildCmd(char* user, char* pass);
