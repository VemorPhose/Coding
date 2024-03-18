#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef struct {
    int top;
    int* array;
} Stack;
typedef struct {
    Stack* s1;
    Stack* s2;
} Queue;
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    stack->array = (int*)malloc(MAX_SIZE * sizeof(int));
    return stack;
}
void push(Stack* stack, int item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
}
int pop(Stack* stack) {
    if (stack->top == -1) {

        printf("Stack underflow\n");
        return -1;
    }
    return stack->array[stack->top--];
}
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->s1 = createStack();
    queue->s2 = createStack();
    return queue;
}
void enqueue(Queue* queue, int item) {
    while (queue->s1->top != -1) {
        push(queue->s2, pop(queue->s1));
    }
    push(queue->s1, item);
    while (queue->s2->top != -1) {
        push(queue->s1, pop(queue->s2));
    }
}
int dequeue(Queue* queue) {
    if (queue->s1->top == -1) {
        printf("Queue is empty\n");
        return -1;
    }
    return pop(queue->s1);
}
int main() {
    Queue* queue = createQueue();
    int choice, item;
    while (1) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter element to enqueue: ");
                scanf("%d", &item);
                enqueue(queue, item);

                break;
            case 2:
                printf("Dequeued item: %d\n", dequeue(queue));
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    free(queue->s1->array);
    free(queue->s1);
    free(queue->s2->array);
    free(queue->s2);
    free(queue);
    return 0;
}