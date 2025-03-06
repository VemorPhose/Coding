#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_ITEMS 10

int buffer[BUFFER_SIZE]; 
int in = 0, out = 0; 

pthread_mutex_t lock; 
sem_t empty_count; 
sem_t full_count;

void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = rand() % 100; 

        sem_wait(&empty_count);
        pthread_mutex_lock(&lock); 

        buffer[in] = item; 
        printf("Producer produced: %d at %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE; 

        pthread_mutex_unlock(&lock);
        sem_post(&full_count); 

        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full_count); 
        pthread_mutex_lock(&lock);

        int item = buffer[out]; 
        printf("Consumer consumed: %d from %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&lock); 
        sem_post(&empty_count); 

        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    pthread_mutex_init(&lock, NULL);
    sem_init(&empty_count, 0, BUFFER_SIZE);
    sem_init(&full_count, 0, 0);

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    pthread_mutex_destroy(&lock);
    sem_destroy(&empty_count);
    sem_destroy(&full_count);

    return 0;
}
