#include "main.h"

int main(int argc, char* argv[]) {

    if (argc > 1) {
        help();
        return 0;
    }
}

void help() {
    printf("\n"
           "Simple text processing.\n"
           "Usage: ./text-processing\n"
           "Functionality: program reads data from stdin word by word. Each word is processed and result is printed to stdout.\n"
           "Words are searched for prime number, correct date and palindrome.\n"
           "\n");
}