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

int main() {
    char inExp[100];
    char postExp[100];
    printf("Enter infix expression: ");
    fgets(inExp, 100, stdin);
    infixToPostfix(inExp, postExp);
    printf("Postfix expression: %s\n", postExp);
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

int main() {
    char inExp[100];
    char postExp[100];
    printf("Enter infix expression: ");
    fgets(inExp, 100, stdin);
    infixToPostfix(inExp, postExp);
    printf("Postfix expression: %s\n", postExp);
    return 0;
}
>>>>>>> af5ab5c21af8834a5b6272908ee927bc90df4ac2
