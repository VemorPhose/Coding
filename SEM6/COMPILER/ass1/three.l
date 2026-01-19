%{
    #include <stdio.h>
%}

%%
([a-z]+) {printf("Small Letter(s): %s\n", yytext);}
[ \t\n]* ;
. ;
%%

int main() {
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}
