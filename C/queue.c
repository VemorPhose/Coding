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
    return queue->rear - queue->front == queue->capacity - 1;
}

int enqueue(Queue queue, Type data){
    if(isFull(queue)) return 0;
    if(isEmpty(queue)){
        queue->front = queue->rear = 0;
        queue->array[queue->front] = data;
    }
    else{
        ++queue->rear;
        queue->array[queue->rear%queue->capacity] = data;
    }
    return 1;
}

int dequeue(Queue queue, Type *data){
    if(isEmpty(queue)) return 0;
    *data = queue->array[queue->front];
    queue->array[(queue->front++)%queue->capacity] = 0;
    if(queue->front > queue->rear)
        queue->front = queue->rear = -1;
    return 1;
}

int front(Queue queue, Type *data){
    if(isEmpty(queue)) return 0;
    *data = queue->array[queue->front%queue->capacity];
    return 1;
}

int rear(Queue queue, Type *data){
    if(isEmpty(queue)) return 0;
    *data = queue->array[queue->rear%queue->capacity];
    return 1;
}

void print(Queue queue, Type data, int status){
    if(isEmpty(queue)){
        printf("\n");
        return;
    }
    for(int i = queue->front; i < queue->rear; i++)
        printf("%d <- ", queue->array[i%queue->capacity]);
    printf("%d\n", queue->array[queue->rear%queue->capacity]);
    printf("data: %d, status: %d\n", data, status);    
    return;
}

int main(){
    Queue queue = newQueue(5);
    Type data = 0;
    int status = 1;
    int f = 1;

    while(f){
        printf("\n0. exit\n");
        printf("1. isEmpty\n");
        printf("2. isFull\n");
        printf("3. queue\n");
        printf("4. dequeue\n");
        printf("5. front\n");
        printf("6. rear\n");
        printf("7. print\n");
        printf("enter choice: ");
        scanf("%d", &f);

        switch(f){
            case 1:
                printf(isEmpty(queue) ? "YES\n" : "NO\n");
                break;
            case 2:
                printf(isFull(queue) ? "YES\n" : "NO\n");
                break;
            case 3:
                printf("enter data: ");
                scanf("%d", &data);
                status = enqueue(queue, data);
                printf(status ? "success\n" : "failed\n");
                break;
            case 4:
                status = dequeue(queue, &data);
                printf(status ? "success\n" : "failed\n");
                break;
            case 5:
                status = front(queue, &data);
                printf("data at front: %d\n", data);
                break;
            case 6:
                status = rear(queue, &data);
                printf("data at rear: %d\n", data);
                break;
            case 7:
                print(queue, data, status);
                break;
            default:
                break;
        }
    }

    return 0;
}