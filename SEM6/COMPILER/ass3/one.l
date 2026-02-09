%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int dd, mm, yyyy, valid;

void parse_numeric(char *input);
void parse_text_date(char *input, int text_first);
int get_month_index(char *str);
void validate_date();
%}

DAY       [0-9]{2}
YEAR       [0-9]{4}
MONTH_TEXT   [a-zA-Z]{3}
SEP     [-/.]

%%

{DAY}{SEP}{DAY}{SEP}{YEAR} {
    parse_numeric(yytext);
    if (valid) {
        printf("Detected: Numeric Format\n");
        printf("Day: %d, Month: %d, Year: %d\n", dd, mm, yyyy);
    }
    else {
        printf("Invalid Date: %s\n", yytext);
    }
}

{DAY}{SEP}{MONTH_TEXT}{SEP}{YEAR} {
    parse_text_date(yytext, 0);
    if (valid) {
        printf("Detected: dd-mmm-yyyy Format\n");
        printf("Day: %dDAY, Month: %d, Year: %d\n", dd, mm, yyyy);
    }
    else {
        printf("Invalid Date: %s\n", yytext);
    }
}

{MONTH_TEXT}{SEP}{DAY}{SEP}{YEAR} {
    parse_text_date(yytext, 1);
    if(valid) {
        printf("Detected: mmm-dd-yyyy Format\n");
        printf("Day: %d, Month: %d, Year: %d\n", dd, mm, yyyy);
    } else {
        printf("Invalid Date: %s\n", yytext);
    }
}

\n  ;
.   ;

%%

int yywrap() { return 1; }

int main() {
    printf("Enter a date:\n");
    yylex();
    return 0;
}

void parse_numeric(char *input) {
    int v1, v2;
    sscanf(input, "%d%*c%d%*c%d", &v1, &v2, &yyyy);

    dd = v1; mm = v2;
    validate_date();

    if (!valid) {
        dd = v2; mm = v1;
        validate_date();
    }
}

void parse_text_date(char *input, int text_first) {
    char m_str[4];
    
    if (text_first) {
        sscanf(input, "%3s%*c%d%*c%d", m_str, &dd, &yyyy);
    } else {
        sscanf(input, "%d%*c%3s%*c%d", &dd, m_str, &yyyy);
    }
    
    mm = get_month_index(m_str);
    validate_date();
}

int get_month_index(char *str) {
    char *months[] = {"JAN", "FEB", "MAR", "APR", "MAY", "JUN", 
                      "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
    char upper[4];
    for(int i=0; i<3; i++) upper[i] = toupper(str[i]);
    upper[3] = '\0';

    for(int i=0; i<12; i++) {
        if(strcmp(upper, months[i]) == 0) return i+1;
    }
    return -1;
}

void validate_date() {
    valid = 1;
    if (yyyy < 1000 || yyyy > 9999) { valid = 0; return; }
    if (mm < 1 || mm > 12) { valid = 0; return; }

    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if ((yyyy % 4 == 0 && yyyy % 100 != 0) || (yyyy % 400 == 0))
        days[2] = 29;

    if (dd < 1 || dd > days[mm]) valid = 0;
}