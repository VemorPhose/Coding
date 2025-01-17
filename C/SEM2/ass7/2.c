<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int top;
    char items[100];
} Stack;

void push(Stack *s, int value) {
    if (s->top == 99) {
        printf("Overflow\n"); 
        exit(1);
    }
    s->items[++(s->top)] = value;
}

int pop(Stack *s) {
    if (s->top == -1) {
        printf("Underflow\n");
        exit(1);
    }
    return s->items[(s->top)--];
}

int evaluatePostfix(char *exp) {
    Stack s; s.top = -1; int i, op1, op2, result;
    for (i = 0; exp[i] != '\0'; i++) {
        if (exp[i] >= '0' && exp[i] <= '9') {
            push(&s, exp[i] - '0');
        }
        else if (exp[i] == ' ' || exp[i] == '\n') {
            continue;
        }
        else {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (exp[i]) {
                case '+':
                    push(&s, op1 + op2);
                    break;
                case '-':
                    push(&s, op1 - op2);
                    break;
                case '*':
                    push(&s, op1 * op2);
                    break;
                case '/':
                    push(&s, op1 / op2);
                    break;
                default:
                    printf("Invalid postfix expression\n");
                    exit(1);
            }
        }
    }
    result = pop(&s);
    return result;
}

int main() {
    char postExp[100];
    printf("Enter postfix expression: ");
    fgets(postExp, 100, stdin);
    int result = evaluatePostfix(postExp);
    printf("Result: %d\n", result);
    return 0;
}
=======
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int top;
    char items[100];
} Stack;

void push(Stack *s, int value) {
    if (s->top == 99) {
        printf("Overflow\n"); 
        exit(1);
    }
    s->items[++(s->top)] = value;
}

int pop(Stack *s) {
    if (s->top == -1) {
        printf("Underflow\n");
        exit(1);
    }
    return s->items[(s->top)--];
}

int evaluatePostfix(char *exp) {
    Stack s; s.top = -1; int i, op1, op2, result;
    for (i = 0; exp[i] != '\0'; i++) {
        if (exp[i] >= '0' && exp[i] <= '9') {
            push(&s, exp[i] - '0');
        }
        else if (exp[i] == ' ' || exp[i] == '\n') {
            continue;
        }
        else {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (exp[i]) {
                case '+':
                    push(&s, op1 + op2);
                    break;
                case '-':
                    push(&s, op1 - op2);
                    break;
                case '*':
                    push(&s, op1 * op2);
                    break;
                case '/':
                    push(&s, op1 / op2);
                    break;
                default:
                    printf("Invalid postfix expression\n");
                    exit(1);
            }
        }
    }
    result = pop(&s);
    return result;
}

int main() {
    char postExp[100];
    printf("Enter postfix expression: ");
    fgets(postExp, 100, stdin);
    int result = evaluatePostfix(postExp);
    printf("Result: %d\n", result);
    return 0;
}
>>>>>>> af5ab5c21af8834a5b6272908ee927bc90df4ac2
