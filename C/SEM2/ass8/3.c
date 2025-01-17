#include <stdio.h>
#include <stdlib.h>

struct queue_t
{
    int *items;
    int front;
    int rear;
    int maxSize;
};

typedef struct queue_t *Queue;

void enqueue(Queue q, int value)
{
    if (q->rear == q->maxSize - 1)
    {
        printf("queue_t is full\n");
    }
    else
    {
        if (q->front == -1)
        {
            q->front = 0;
        }
        q->items[++q->rear] = value;
    }
}

int dequeue(Queue q)
{
    int item;
    if (q->front == -1)
    {
        printf("queue_t is empty\n");
        item = -1;
    }
    else
    {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear)
        {
            q->front = q->rear = -1;
        }
    }
    return item;
}

struct Stack
{
    Queue q1;
    Queue q2;
    int maxSize;
};

void push(struct Stack *s)
{
    int value;
    printf("enter the value to be pushed in stack: \n");
    scanf("%d", &value);
    enqueue(s->q1, value);
}

int pop(struct Stack *s)
{
    int i, item;
    while (s->q1->front != s->q1->rear)
    {
        enqueue(s->q2, dequeue(s->q1));
    }

    item = dequeue(s->q1);

    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;

    return item;
}

int main()
{
    int maxSize;
    printf("Enter the maximum size of the stack: ");
    scanf("%d", &maxSize);

    Queue q1 = (Queue)malloc(sizeof(struct queue_t));
    Queue q2 = (Queue)malloc(sizeof(struct queue_t));

    q1->items = (int *)malloc(maxSize * sizeof(int));
    q2->items = (int *)malloc(maxSize * sizeof(int));
    q1->front = q1->rear = -1;
    q2->front = q2->rear = -1;
    q1->maxSize = q2->maxSize = maxSize;

    struct Stack *s = (struct Stack *)malloc(sizeof(struct Stack));
    s->q1 = q1;
    s->q2 = q2;
    s->maxSize = maxSize;

    for (int i = 0; i < maxSize; i++)
        push(s);
    printf("Popped elements: \n");
    for (int i = 0; i < maxSize; i++)
        printf("%d, ", pop(s));
    printf("\n");

    free(q1->items);
    free(q2->items);
    free(q1);
    free(q2);
    free(s);

    return 0;
}