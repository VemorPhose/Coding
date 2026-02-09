%{
#include <stdio.h>
#include <string.h>
#include <strings.h>

int ddl_ctr = 0;
int dml_ctr = 0;

char *ddl_list[] = {"CREATE", "ALTER", "DROP", "TRUNCATE", "RENAME", "COMMENT", NULL};
char *dml_list[] = {"INSERT", "UPDATE", "DELETE", NULL};

void check_and_count(char *str);
%}

WORD [a-zA-Z]+

%%

{WORD} { check_and_count(yytext); }
.|\n   ;

%%

int yywrap() {
    return 1;
}

void check_and_count(char *str) {
    int i;
    
    for(i = 0; ddl_list[i] != NULL; i++) {
        if(strcasecmp(str, ddl_list[i]) == 0) {
            ddl_ctr++;
            return;
        }
    }

    for(i = 0; dml_list[i] != NULL; i++) {
        if(strcasecmp(str, dml_list[i]) == 0) {
            dml_ctr++;
            return;
        }
    }
}

int main(int argc, char **argv) {
    if(argc > 1) {
        yyin = fopen(argv[1], "r");
        if(!yyin) {
            printf("Could not open file\n");
            return 1;
        }
    }

    yylex();

    printf("DDL: %d\n", ddl_ctr);
    printf("DML: %d\n", dml_ctr);

    return 0;
}