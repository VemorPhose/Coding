#include <stdio.h>
#include <ctype.h>

int main (int argc, char *argv[]) {
    FILE* input = stdin;
    FILE* output = stdout;

    int c = fgetc(input);
    int cnt = 0;
    while (c != EOF) {
        if (!isalpha(c)) {
            cnt++;
        }
        fputc(c, output);
        c = fgetc(input);
    }

    fprintf(stderr, "Number of non-alphabetic characters: %d\n", cnt);
    exit(0);
    return 0;
}