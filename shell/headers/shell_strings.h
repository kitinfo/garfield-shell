#pragma once
#include <stdbool.h>

/**
 * deletes the first <len> chars from input and writes the rest
 * to dest.
 */
void sFirstCut(char* input, char* dest, int len);

/**
 * checks if two strings are equal
 */
bool sequals(char* one, char* two);


 /**
  * checks if string longer begins with string shorter
  */
bool begins(char* longer, char* shorter);
