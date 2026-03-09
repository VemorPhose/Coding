%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
void yyerror(const char *s);
%}

%token SELECT FROM WHERE INSERT INTO VALUES UPDATE SET DELETE CREATE TABLE
%token ALTER DROP TRUNCATE ADD GROUP BY HAVING ORDER ASC DESC LIMIT
%token JOIN INNER LEFT RIGHT FULL ON AS AND OR NOT IN IS NULLX BETWEEN LIKE DISTINCT
%token COUNT SUM AVG MIN MAX INT_TYPE VARCHAR_TYPE
%token IDENTIFIER NUMBER STRING

%%
queries:
    | queries query
    ;

query:
    select_query opt_semi { printf("=> Valid SELECT query.\n"); }
    | insert_query opt_semi { printf("=> Valid INSERT query.\n"); }
    | update_query opt_semi { printf("=> Valid UPDATE query.\n"); }
    | delete_query opt_semi { printf("=> Valid DELETE query.\n"); }
    | create_query opt_semi { printf("=> Valid CREATE query.\n"); }
    | alter_query opt_semi  { printf("=> Valid ALTER query.\n"); }
    | drop_query opt_semi   { printf("=> Valid DROP query.\n"); }
    | truncate_query opt_semi { printf("=> Valid TRUNCATE query.\n"); }
    | error opt_semi { yyerrok; }
    ;

opt_semi:
    /* empty */
    | ';'
    ;

/* DML Commands */
select_query:
    SELECT opt_distinct column_list FROM IDENTIFIER opt_join opt_where opt_group opt_having opt_order opt_limit
    ;

insert_query:
    INSERT INTO IDENTIFIER VALUES '(' value_list ')'
    ;

update_query:
    UPDATE IDENTIFIER SET assignment_list opt_where
    ;

delete_query:
    DELETE FROM IDENTIFIER opt_where
    ;

/* DDL Commands */
create_query:
    CREATE TABLE IDENTIFIER '(' column_def_list ')'
    ;

alter_query:
    ALTER TABLE IDENTIFIER ADD IDENTIFIER data_type
    | ALTER TABLE IDENTIFIER DROP IDENTIFIER
    ;

drop_query:
    DROP TABLE IDENTIFIER
    ;

truncate_query:
    TRUNCATE TABLE IDENTIFIER
    ;

/* Selection modifiers */
opt_distinct:
    /* empty */
    | DISTINCT
    ;

column_list:
    '*'
    | select_item_list
    ;

select_item_list:
    select_item
    | select_item_list ',' select_item
    ;

select_item:
    IDENTIFIER opt_alias
    | IDENTIFIER '.' IDENTIFIER opt_alias
    | aggregate_func '(' '*' ')' opt_alias
    | aggregate_func '(' IDENTIFIER ')' opt_alias
    ;

aggregate_func:
    COUNT | SUM | AVG | MIN | MAX
    ;

opt_alias:
    /* empty */
    | AS IDENTIFIER
    | IDENTIFIER
    ;

/* Joins */
opt_join:
    /* empty */
    | join_type JOIN IDENTIFIER ON IDENTIFIER '.' IDENTIFIER '=' IDENTIFIER '.' IDENTIFIER
    ;

join_type:
    /* empty */
    | INNER | LEFT | RIGHT | FULL
    ;

/* Filtering & Grouping */
opt_where:
    /* empty */
    | WHERE condition_list
    ;

opt_group:
    /* empty */
    | GROUP BY ident_list
    ;

opt_having:
    /* empty */
    | HAVING condition_list
    ;

opt_order:
    /* empty */
    | ORDER BY ident_list opt_dir
    ;

opt_dir:
    /* empty */
    | ASC | DESC
    ;

opt_limit:
    /* empty */
    | LIMIT NUMBER
    ;

ident_list:
    IDENTIFIER
    | ident_list ',' IDENTIFIER
    ;

/* Conditions */
condition_list:
    condition
    | condition_list AND condition
    | condition_list OR condition
    ;

condition:
    IDENTIFIER '=' value
    | IDENTIFIER '<' value
    | IDENTIFIER '>' value
    | IDENTIFIER LIKE STRING
    | IDENTIFIER BETWEEN value AND value
    | IDENTIFIER IN '(' value_list ')'
    | IDENTIFIER IS NULLX
    | IDENTIFIER IS NOT NULLX
    | aggregate_func '(' IDENTIFIER ')' '>' NUMBER
    ;

/* Values & Data Types */
value:
    NUMBER
    | STRING
    ;

value_list:
    value
    | value_list ',' value
    ;

assignment_list:
    IDENTIFIER '=' value
    | assignment_list ',' IDENTIFIER '=' value
    ;

column_def_list:
    column_def
    | column_def_list ',' column_def
    ;

column_def:
    IDENTIFIER data_type
    ;

data_type:
    INT_TYPE
    | VARCHAR_TYPE '(' NUMBER ')'
    ;

%%
void yyerror(const char *s) {
    fprintf(stderr, "=> Syntax Error: Invalid query.\n");
}

int main() {
    printf("Enter SQL queries (Ctrl+D to exit):\n");
    yyparse();
    return 0;
}