#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Type;
typedef struct stack_t *Stack;

struct stack_t {
    Type *array;
    unsigned int capacity;
    int top;
};

Stack newStack(unsigned int capacity){
    Stack stack = (Stack) calloc (1, sizeof(struct stack_t));
    assert(stack);
    stack->array = (Type*) calloc (capacity, sizeof(Type));
    assert(stack->array);
    stack->capacity = capacity;
    stack->top = -1;
    return stack;
}

int isEmpty(Stack stack){
    return stack->top == -1;
}

int isFull(Stack stack){
    return stack->top == stack->capacity - 1;
}

int push(Stack stack, Type data){
    if(isFull(stack)) return 0;
    stack->array[++stack->top] = data;
    return 1;
}

int pop(Stack stack, Type *data){
    if(isEmpty(stack)) return 0;
    *data = stack->array[stack->top];
    stack->array[stack->top--] = 0;
    return 1;
}

int peek(Stack stack, Type *data){
    if(isEmpty(stack)) return 0;
    *data = stack->array[stack->top];
    return 1;
}

int size(Stack stack){
    return stack->top + 1;
}

void print(Stack stack, Type data, int status){
    for(int i = 0; i <= stack->top; i++)
        printf("%d ", stack->array[i]);
    printf("\n");
    printf("data: %d, status: %d\n", data, status);
    return;
}

int main(){
    Stack stack = newStack(8);
    Type data = 0;
    int status = 1;
    int f = 1;
    while(f){
        printf("\n0. exit\n");
        printf("1. isEmpty\n");
        printf("2. isFull\n");
        printf("3. push\n");
        printf("4. pop\n");
        printf("5. peek\n");
        printf("6. size\n");
        printf("7. print\n");
        printf("enter choice: ");
        scanf("%d", &f);

        switch(f){
            case 1:
                printf(isEmpty(stack) ? "YES\n" : "NO\n");
                break;
            case 2:
                printf(isFull(stack) ? "YES\n" : "NO\n");
                break;
            case 3:
                printf("enter data: ");
                scanf("%d", &data);
                status = push(stack, data);
                printf(status ? "success\n" : "failed\n");
                break;
            case 4:
                status = pop(stack, &data);
                printf(status ? "success\n" : "failed\n");
                break;
            case 5:
                status = peek(stack, &data);
                printf("data at top: %d\n", data);
                break;
            case 6:
                printf("size of stack: %d", size(stack));
                break;
            case 7:
                print(stack, data, status);
                break;
            default:
                break;
        }
    }

    return 0;
}