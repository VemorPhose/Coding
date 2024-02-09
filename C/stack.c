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

void print(Stack stack){
    for(int i = 0; i <= stack->top; i++)
        printf("%d ", stack->array[i]);
    printf("\n");
    return;
}

int main(){
    Stack stack = newStack(5);
    Type data = 0;

    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    push(stack, 4);
    push(stack, 5);
    print(stack);
    push(stack, 6);
    print(stack);
    pop(stack, &data);
    print(stack);
    printf("%d\n", data);
    peek(stack, &data);
    print(stack);
    printf("%d\n", data);

    return 0;
}