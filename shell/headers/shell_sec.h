#pragma once
#include <stdbool.h>

void freeSec();

void setPassword(char* pass);

void setUser(char* username);

void askPassword();

void checkLogin();

char* getPassword();

char* getUser();

void initSec();

void setPGPass(bool flag);

bool getPGPass();
