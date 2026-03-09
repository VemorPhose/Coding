%{
#include "y.tab.h"
%}

%%
(?i:select)   { return SELECT; }
(?i:from)     { return FROM; }
(?i:where)    { return WHERE; }
(?i:insert)   { return INSERT; }
(?i:into)     { return INTO; }
(?i:values)   { return VALUES; }
(?i:update)   { return UPDATE; }
(?i:set)      { return SET; }
(?i:delete)   { return DELETE; }
(?i:create)   { return CREATE; }
(?i:table)    { return TABLE; }
(?i:alter)    { return ALTER; }
(?i:drop)     { return DROP; }
(?i:truncate) { return TRUNCATE; }
(?i:add)      { return ADD; }
(?i:group)    { return GROUP; }
(?i:by)       { return BY; }
(?i:having)   { return HAVING; }
(?i:order)    { return ORDER; }
(?i:asc)      { return ASC; }
(?i:desc)     { return DESC; }
(?i:limit)    { return LIMIT; }
(?i:join)     { return JOIN; }
(?i:inner)    { return INNER; }
(?i:left)     { return LEFT; }
(?i:right)    { return RIGHT; }
(?i:full)     { return FULL; }
(?i:on)       { return ON; }
(?i:as)       { return AS; }
(?i:and)      { return AND; }
(?i:or)       { return OR; }
(?i:not)      { return NOT; }
(?i:in)       { return IN; }
(?i:is)       { return IS; }
(?i:null)     { return NULLX; }
(?i:between)  { return BETWEEN; }
(?i:like)     { return LIKE; }
(?i:distinct) { return DISTINCT; }
(?i:count)    { return COUNT; }
(?i:sum)      { return SUM; }
(?i:avg)      { return AVG; }
(?i:min)      { return MIN; }
(?i:max)      { return MAX; }
(?i:int)      { return INT_TYPE; }
(?i:varchar)  { return VARCHAR_TYPE; }

[a-zA-Z_][a-zA-Z0-9_]* { return IDENTIFIER; }
[0-9]+                 { return NUMBER; }
'[^']*'                { return STRING; }

"="|"<"|">"|"*"|","|";"|"("|")"|"." { return yytext[0]; }

[ \t\n\r]+             { }
.                      { return yytext[0]; }
%%

int yywrap() {
    return 1;
}