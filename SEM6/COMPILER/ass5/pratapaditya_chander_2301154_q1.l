%{
#include "one.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+          { return NUMBER; }
[ \t]           { }
\n              { return '\n'; }
"+"|"-"|"*"|"/" { return yytext[0]; }
"("|")"         { return yytext[0]; }
.               { }

%%

int yywrap(void) {
    return 1;
}
