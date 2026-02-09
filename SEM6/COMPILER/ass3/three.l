%{
#include <stdio.h>
#include <string.h>

int valid = 1;
int paren_count = 0;
int expect_operand = 1;

int id_count = 0;
int op_count = 0;
int lt_count = 0;

%}

IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*
NUMBER     [0-9]+(\.[0-9]+)?
OPERATOR   [\+\-\*\/\=%]
OPEN_PAR   "("
CLOSE_PAR  ")"

%%

{IDENTIFIER} {
    if (!expect_operand) { valid = 0; }
    printf("Identifier: %s\n", yytext);
    id_count++;
    expect_operand = 0;
}

{NUMBER} {
    if (!expect_operand) { valid = 0; }
    printf("Literal: %s\n", yytext);
    lt_count++;
    expect_operand = 0; 
}

{OPERATOR} {
    if (expect_operand) { valid = 0; }
    printf("Operator  : %s\n", yytext);
    op_count++;
    expect_operand = 1;
}

{OPEN_PAR} {
    paren_count++;
    expect_operand = 1; 
}

{CLOSE_PAR} {
    paren_count--;
    if (paren_count < 0) valid = 0;
    if (expect_operand) valid = 0;
    expect_operand = 0; 
}

[ \t\n] ;

. { 
    printf("Unknown Character: %s\n", yytext);
    valid = 0; 
}

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter an arithmetic expression (e.g., a = b + c * 10):\n");
    yylex();

    if (paren_count != 0) {
        valid = 0;
        printf("\nError: Unbalanced Parentheses\n");
    }
    if (expect_operand == 1 && op_count > 0) {
        valid = 0;
    }

    if (valid && id_count > 0) {
        printf("Result: VALID Expression\n");
        printf("Total Identifiers: %d\n", id_count);
        printf("Total Operators  : %d\n", op_count);
    } else {
        printf("Result: INVALID Expression\n");
    }

    return 0;
}