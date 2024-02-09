#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int Type;
typedef struct queue_t *Queue;

struct queue_t {
    int *array;
    unsigned int capacity;
    int front, rear;
};

Queue newQueue(unsigned int capacity){
    Queue queue = (Queue) calloc (1, sizeof(struct queue_t));
    assert(queue);
    queue->array = (Type*) calloc (capacity, sizeof(Type));
    assert(queue->array);
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
}

int isEmpty(Queue queue){
    return queue->front == -1 && queue->rear == -1;
}

int isFull(Queue queue){
    return queue->rear == queue->capacity - 1;
}

int enqueue(Queue queue, Type data){
    if(isFull(queue)) return 0;
    if(isEmpty){
        queue->front = queue->rear = 0;
        queue->array[queue->front] = data;
    }
    else
        queue->array[++queue->rear] = data;
    return 1;
}

int dequeue(Queue queue, Type *data){
    if(isEmpty(queue)) return 0;
    *data = queue->array[queue->front];
    queue->array[queue->front++] = 0;
    if(queue->front > queue->rear)
        queue->front = queue->rear = -1;
    return 1;
}

int front(Queue queue, Type *data){
    if(isEmpty(queue)) return 0;
    *data = queue->array[queue->front];
    return 1;
}

int rear(Queue queue, Type *data){
    if(isEmpty(queue)) return 0;
    *data = queue->array[queue->rear];
    return 1;
}

void print(Queue queue){
    if(isEmpty(queue)){
        printf("\n");
        return;
    }
    for(int i = queue->front; i <= queue->rear; i++)
        printf("%d ", queue->array[i]);
    printf("\n");
    return;
}

int main(){
    Queue queue = newQueue(5);
    Type data = 0;

    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    enqueue(queue, 5);
    print(queue);
    enqueue(queue, 6);
    print(queue);
    dequeue(queue, &data);
    print(queue);
    printf("%d\n", data);

    return 0;
}