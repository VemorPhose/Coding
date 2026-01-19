%{
    #include <stdio.h>
%}

%%
[ \t\n]+(A|a|AN|An|an|THE|The|the) {printf("Articles: %s\n", yytext);}
(A|a|AN|An|an|THE|The|the)[ \t\n]+ {printf("Articles: %s\n", yytext);}
. ;
%%

int main() {
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}
