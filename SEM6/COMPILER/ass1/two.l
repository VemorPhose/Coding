%{
    #include <stdio.h>
%}

%%
[ \t\n]+(A|a|AN|An|an|THE|The|the) {printf("Articles: %s\n", yytext);}
(A|a|AN|An|an|THE|The|the)[ \t\n]+ {printf("Articles: %s\n", yytext);}
[ \t\n]+(go|GO|Go|eat|EAT|Eat) { printf("Verbs: %s\n", yytext); }
(go|GO|Go|eat|EAT|Eat)[ \t\n]+ { printf("Verbs: %s\n", yytext); }
. ;
%%

int main() {
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}
