#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    FILE* input = stdin;
    FILE* output = stdout;

    int c = fgetc(input);
    while (c != EOF) {
        if (isalpha(c)) {
            c ^= ' ';
        }
        fputc(c, output);
        c = fgetc(input);
    }
    exit(0);
    return 0;
}