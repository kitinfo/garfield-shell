#pragma once

#define MAXLENGTH 100
#define MATE 0


int main(int argc, char* argv[]);

int shell();

void read_line(char* dest);

bool sequals(char* one, char* two);

void parseArguments(int argc, char* argv[]);

void printHelp();

void parseSet(char* input);

bool begins(char* longer, char* shorter);

void sFirstCut(char* input, char* dest, int len);

void setUser(char* username);

void setPassword(char* pass);

void parseList(char* input);

void askPassword();

void printInternHelp();

void buy(char* input);

void buyMate();

void buySnacks(char* input);

void execBuy(int id);

int getSnackID(char* snack);

