%{
    #include <stdio.h>
%}

%%
"//".* ;
"/*"([^*]|\*+[^*/])*"*/" ;
%%

int main() {
    /* yyin and yyout as pointer
    of File type */
    extern FILE *yyin, *yyout;

    /* yyin points to the file input.txt
    and opens it in read mode*/
    yyin = fopen("input.java", "r");

    /* yyout points to the file output.txt
    and opens it in write mode*/
    yyout = fopen("output.java", "w");

    yylex();
    return 0;
}

int yywrap(){
    return 1;
}