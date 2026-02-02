%{
    #include <stdio.h>
%}

%%
([a-z]+) {printf("%s", yytext);}
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
