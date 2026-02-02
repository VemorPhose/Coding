%{
#include <stdio.h>
#include <string.h>

static char tags[100][50];
static int counts[100];
static int counter = 0;

void process_tag(char *tag)
{
    int i;
    for (i = 0; i < counter; i++) {
        if (strcmp(tags[i], tag) == 0) {
            counts[i]++;
            return;
        }
    }

    strcpy(tags[counter], tag);
    counts[counter] = 1;
    counter++;
}
%}

%%

("<"|"</")[a-zA-Z]+   {
                        char tag[50];
                        int i = 0, j = 0;

                        if (yytext[1] == '/')
                            i = 2;
                        else
                            i = 1;

                        while (yytext[i] != '\0')
                            tag[j++] = yytext[i++];

                        tag[j] = '\0';
                        process_tag(tag);
                     }

.|\n                ;

%%

int main()
{
    extern FILE *yyin;
    yyin = fopen("input.html", "r");

    int i;
    for (i = 0; i < 100; i++)
        counts[i] = 0;

    yylex();

    for (i = 0; i < counter; i++)
        printf("%s: %d\n", tags[i], counts[i]);

    return 0;
}

int yywrap()
{
    return 1;
}
