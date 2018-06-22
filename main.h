#ifndef TEXT_PROCESSING_MAIN_H
#define TEXT_PROCESSING_MAIN_H

#include <stdio.h>	//stdin, stdout
#include <time.h>	//mktime
#include <limits.h>	//INT_MAX
#include <ctype.h>	//isdigit
#include <errno.h>	//errno

typedef enum {false, true} bool;

void help();
int length(char s[]);
bool is_number(char s[]);
int to_int(char s[], int start, int len);
bool is_prime(char s[]);
bool date_check_and_print(char s[]);
void zero_cropped_print(char s[]);
bool is_palindrome(char s[]);
bool is_printable(char s[]);

#endif //TEXT_PROCESSING_MAIN_H
