#include "main.h"

//global constants
#define MAX 100
#define DAY_MIN 1
#define DAY_MAX 31
#define MONTH_MIN 0
#define MONTH_MAX 11
#define DATE_LENGTH 10
#define DECADE 10
#define FIRST_DASH 4
#define SECOND_DASH 7
#define TO_YEAR 1900
#define YEAR_START 0
#define YEAR_LENGTH 4
#define MONTH_START 5
#define MONTH_LENGTH 2
#define DAY_START 8
#define DAY_LENGTH 2
#define TO_INT 48

int main(int argc, char* argv[]) {

    if (argc > 1) {
        help();
        return 0;
    }

    char str[MAX+1];

    fprintf(stderr, "Write words, confirm with Enter:\n");

    //reading input
    while ((scanf("%100s", str)) == 1) {
        if (!is_printable(str)) {
            fprintf(stderr, "Invalid input. Contains non printable characters.\n");
        } else if (is_number(str)) {
            zero_cropped_print(str);

            if (is_prime(str)) {
                printf(" (prime)");
            }
            printf("\n");
        } else if (!date_check_and_print(str)) {
            printf("word: %s", str);
            if (is_palindrome(str)) {
                printf(" (palindrome)");
            }
            printf("\n");
        }
    }

    if (errno != 0) {
        perror("Error");
    }

    return 0;
}

void help() {
    printf("\n"
           "Simple text processing.\n"
           "Usage: ./text-processing\n"
           "Functionality: program reads data from stdin word by word. Each word is processed and result is printed to stdout.\n"
           "Words are searched for prime number, correct date and palindrome. Correct date is in format yyyy-mm-dd.\n"
           "\n");
}

/**
 * Counts number of characters in word
 * @param s     word
 * @return      length of word
 */
int length(char s[]) {
    int i = 0;

    while (s[i] != '\0') {
        i++;
    }
    return i;
}

/**
 * Determines, if given character array contains figures only
 * @param s     character array
 * @return      true, if input contains figures only, false otherwise
 */
bool is_number(char s[]) {
    int len = length(s);

    for (int i = 0; i < len; i++) {
        if (!isdigit(s[i]))	{
            return false;
        }
    }
    return true;
}

/**
 * Converts character array to integer. Allowed range is [0, INT_MAX].
 * @param s         character array to convert
 * @param start     position of first character to convert
 * @param len       number of character to convert
 * @return          integer value of character array, -1 in case of failure
 */
int to_int(char s[], int start, int len) {
    int num = 0;

    for (int i = start; i < start + len; i++) {
        //test, if num*10 is in range
        if (INT_MAX / DECADE < num) {
            return -1;
        } else {
            num *= DECADE;
        }

        //test, if next figure is still in range
        if (INT_MAX - s[i] - TO_INT < num) {
            return -1;
        } else {
            num += s[i] - TO_INT;
        }
    }
    return num;
}

/**
 * Determines if given character array is prime number
 * @param s     character array
 * @return      true, if character array is prime number, false otherwise
 */
bool is_prime(char s[]) {
    int num = to_int(s,0,length(s));

    if (num == -1) {
        return false;
    }

    if (num == 1) {
        return false;
    }

    if (num <= 3) {
        return true;
    }

    if (num % 2 == 0 || num % 3 == 0) {
        return false;
    }

    int i = 5;

    while (i*i <= num + 1) {
        if (num % i == 0|| num % (i + 2) == 0) {
            return false;
        }
        i += 6;
    }

    return true;
}

/**
 * Validate character array as date and prints it to stdout
 * @param s     character array
 * @return      true, if character array is valid date, false otherwise
 */
bool date_check_and_print(char s[]) {
    //date have to be 10 characters long
    if (length(s) != DATE_LENGTH) {
        return false;
    }

    //date have to have dashes at correct places
    if (s[FIRST_DASH] != '-' || s[SECOND_DASH] != '-') {
        return false;
    }

    //other characters have to be numbers
    for (int i = 0; i < DATE_LENGTH; i++) {
        if ((!isdigit(s[i])) && i != FIRST_DASH && i != SECOND_DASH) {
            return false;
        }
    }

    //parsing year, month, day from inpuy
    int year = to_int(s,YEAR_START,YEAR_LENGTH) - TO_YEAR;	//correction for mktime function (year - 1900)
    int month = to_int(s,MONTH_START,MONTH_LENGTH) - 1;	//correction for mktime function (months in range 0 - 11)
    int day = to_int(s,DAY_START,DAY_LENGTH);

    //validate day and month values
    if (day < DAY_MIN || day > DAY_MAX || month < MONTH_MIN || month > MONTH_MAX) {
        return false;
    }

    struct tm info;
    const char* weekday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    info.tm_year = year;
    info.tm_mon = month;
    info.tm_mday = day;
    info.tm_hour = 0;
    info.tm_min = 0;
    info.tm_sec = 1;
    info.tm_isdst = -1;

    if (mktime(&info) == -1) {
        return false;
    }

    printf("date: %s %s\n", weekday[info.tm_wday], s);

    return true;
}

/**
 * Prints character array without opening zeros
 * @param s     character array
 */
void zero_cropped_print(char s[]) {
    char cropped[MAX+1];
    int i = 0;

    //pointer 'i' to first non zero position
    while (s[i] == '0') {
        i++;
    }

    //we are at the end - all characters were zero
    if (s[i] == '\0') {
        printf("number: 0");
    } else {
        //copy non zero part of character array
        for (int j = i; j <= length(s); j++)
        {
            cropped[j-i] = s[j];
        }

        printf("number: %s", cropped);
    }
}

/**
 * Determines, if character array is palindrome
 * @param s     character array
 * @return      true, if character array is palindrome, false otherwise
 */
bool is_palindrome(char s[]) {
    if (s[0] == '\0') {
        return false;
    }

    int len = length(s);

    for (int i = 0; i < len / 2; i++) {
        if (s[i] != s[len - i - 1]) {
            return false;
        }
    }

    return true;
}

/**
 * Determines, if character array contains only printable characters
 * @param s     character array
 * @return      true, if character array contains printable characters only, false otherwise
 */
bool is_printable(char s[]) {
    int len = length(s);

    for (int i = 0; i < len; i++) {
        if (isprint(s[i]) == 0) {
            return false;
        }
    }

    return true;
}