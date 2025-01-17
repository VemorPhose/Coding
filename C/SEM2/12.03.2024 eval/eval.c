<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

typedef struct {
    int top;
    char items[100];
} Stack;

void push(Stack *s, int value) {
    if (s->top == 99) {
        printf("Overflow\n");
        return;
    }
    s->items[++(s->top)] = value;
}

int pop(Stack *s) {
    if (s->top == -1) {
        printf("Underflow\n");
        return 0;
    }
    return s->items[(s->top)--];
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

void infixToPostfix(char *inExp, char *postExp) {
    Stack s; s.top = -1;
    int i, j;
    char token, popped;
    for (i = 0, j = 0; inExp[i] != '\0'; i++) {
        token = inExp[i];
        if (token == ' ') {
            continue;
        }
        else if ((token >= '0' && token <= '9') || (token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z')) {
            postExp[j++] = token;
        }
        else if (token == '(') {
            push(&s, token);
        }
        else if (token == ')') {
            while ((popped = pop(&s)) != '(') {
                postExp[j++] = popped;
            }
        }
        else {
            while (s.top != -1 && precedence(s.items[s.top]) >= precedence(token)) {
                postExp[j++] = pop(&s);
            }
            push(&s, token);
        }
    }
    while (s.top != -1) {
        postExp[j++] = pop(&s);
    }
    postExp[j] = '\0';
}

void sToPoly(int *p, char *s){
    int flag = 0;
    int sign = 0;
    int coeff = 0;
    int exp = 0;
    for(int i = 0, j = 0; s[i] != 0; i++){
        if(s[i] == ' ')
            continue;
        if(s[i] == '+' || s[i] == '-'){
            if(!coeff){
                if(s[i] == '+')
                    sign = 0;
                else sign = 1;
                continue;
            }
            if(flag == 1 && exp == 0)
                exp = 1;
            if(sign)
                p[exp] -= coeff;
            else p[exp] += coeff;
            coeff = flag = exp = 0;
            if(s[i] == '+')
                sign = 0;
            else sign = 1;
        }
        else if(s[i] == 'x')
            flag = 1;
        else{
            if(!flag){
                coeff *= 10;
                coeff += s[i] - '0';
            }
            else{
                exp *= 10;
                exp += s[i] - '0';
            }
        }
    }
    if(!coeff);
    else if(flag == 1 && exp == 0)
        exp = 1;
    if(sign)
        p[exp] -= coeff;
    else p[exp] += coeff;
}

int main(){
    int p1[100], p2[100];
    char s1[1000], s2[1000];
    for(int i = 0; i < 100; i++) p1[i] = p2[i] = 0;
    printf("Enter polynomial 1 in x: ");
    scanf("%[^\n]%*c", s1);
    printf("Enter polynomial 2 in x: ");
    scanf("%[^\n]%*c", s2);
    sToPoly(p1, s1);
    sToPoly(p2, s2);
    for(int i = 0; i < 100; i++)
        p1[i] += p2[i];

    int in = 0;
    for(int i = 99; i >= 0; i--){
        if(!p1[i])
            continue;
        if(p1[i]<0){
            s1[in++] = '-';
            s1[in++] = '0' - p1[i];
            s1[in++] = 'x';
            s1[in++] = i + '0';
        }
        else {
            s1[in++] = '+';
            s1[in++] = '0' + p1[i];
            s1[in++] = 'x';
            s1[in++] = i + '0';
        }
    }
    s1[in] = 0;
    printf("%s\n", s1);

    infixToPostfix(s1, s2);
    printf("Postfix expression: %s\n", s2);
    return 0;


    return 0;
}

=======
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

typedef struct {
    int top;
    char items[100];
} Stack;

void push(Stack *s, int value) {
    if (s->top == 99) {
        printf("Overflow\n");
        return;
    }
    s->items[++(s->top)] = value;
}

int pop(Stack *s) {
    if (s->top == -1) {
        printf("Underflow\n");
        return 0;
    }
    return s->items[(s->top)--];
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

void infixToPostfix(char *inExp, char *postExp) {
    Stack s; s.top = -1;
    int i, j;
    char token, popped;
    for (i = 0, j = 0; inExp[i] != '\0'; i++) {
        token = inExp[i];
        if (token == ' ') {
            continue;
        }
        else if ((token >= '0' && token <= '9') || (token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z')) {
            postExp[j++] = token;
        }
        else if (token == '(') {
            push(&s, token);
        }
        else if (token == ')') {
            while ((popped = pop(&s)) != '(') {
                postExp[j++] = popped;
            }
        }
        else {
            while (s.top != -1 && precedence(s.items[s.top]) >= precedence(token)) {
                postExp[j++] = pop(&s);
            }
            push(&s, token);
        }
    }
    while (s.top != -1) {
        postExp[j++] = pop(&s);
    }
    postExp[j] = '\0';
}

void sToPoly(int *p, char *s){
    int flag = 0;
    int sign = 0;
    int coeff = 0;
    int exp = 0;
    for(int i = 0, j = 0; s[i] != 0; i++){
        if(s[i] == ' ')
            continue;
        if(s[i] == '+' || s[i] == '-'){
            if(!coeff){
                if(s[i] == '+')
                    sign = 0;
                else sign = 1;
                continue;
            }
            if(flag == 1 && exp == 0)
                exp = 1;
            if(sign)
                p[exp] -= coeff;
            else p[exp] += coeff;
            coeff = flag = exp = 0;
            if(s[i] == '+')
                sign = 0;
            else sign = 1;
        }
        else if(s[i] == 'x')
            flag = 1;
        else{
            if(!flag){
                coeff *= 10;
                coeff += s[i] - '0';
            }
            else{
                exp *= 10;
                exp += s[i] - '0';
            }
        }
    }
    if(!coeff);
    else if(flag == 1 && exp == 0)
        exp = 1;
    if(sign)
        p[exp] -= coeff;
    else p[exp] += coeff;
}

int main(){
    int p1[100], p2[100];
    char s1[1000], s2[1000];
    for(int i = 0; i < 100; i++) p1[i] = p2[i] = 0;
    printf("Enter polynomial 1 in x: ");
    scanf("%[^\n]%*c", s1);
    printf("Enter polynomial 2 in x: ");
    scanf("%[^\n]%*c", s2);
    sToPoly(p1, s1);
    sToPoly(p2, s2);
    for(int i = 0; i < 100; i++)
        p1[i] += p2[i];

    int in = 0;
    for(int i = 99; i >= 0; i--){
        if(!p1[i])
            continue;
        if(p1[i]<0){
            s1[in++] = '-';
            s1[in++] = '0' - p1[i];
            s1[in++] = 'x';
            s1[in++] = i + '0';
        }
        else {
            s1[in++] = '+';
            s1[in++] = '0' + p1[i];
            s1[in++] = 'x';
            s1[in++] = i + '0';
        }
    }
    s1[in] = 0;
    printf("%s\n", s1);

    infixToPostfix(s1, s2);
    printf("Postfix expression: %s\n", s2);
    return 0;


    return 0;
}

>>>>>>> af5ab5c21af8834a5b6272908ee927bc90df4ac2
