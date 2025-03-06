#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Define buffer capacity
#define NUM_ITEMS 10   // Number of items each producer will produce

int buffer[BUFFER_SIZE]; // Shared buffer
int in = 0, out = 0; // Buffer index trackers

pthread_mutex_t lock; // Mutex for buffer access
sem_t empty_count; // Semaphore to track empty slots
sem_t full_count;  // Semaphore to track filled slots

// Producer function
void *producer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        int item = rand() % 100; // Generate a random item

        sem_wait(&empty_count); // Wait if buffer is full
        pthread_mutex_lock(&lock); // Lock buffer access

        buffer[in] = item; // Insert item into buffer
        printf("Producer produced: %d at %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE; // Move index circularly

        pthread_mutex_unlock(&lock); // Unlock buffer access
        sem_post(&full_count); // Signal that an item is available

        sleep(1); // Simulate production time
    }
    return NULL;
}

// Consumer function
void *consumer(void *arg) {
    for (int i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full_count); // Wait if buffer is empty
        pthread_mutex_lock(&lock); // Lock buffer access

        int item = buffer[out]; // Remove item from buffer
        printf("Consumer consumed: %d from %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE; // Move index circularly

        pthread_mutex_unlock(&lock); // Unlock buffer access
        sem_post(&empty_count); // Signal that a slot is empty

        sleep(1); // Simulate consumption time
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize synchronization primitives
    pthread_mutex_init(&lock, NULL);
    sem_init(&empty_count, 0, BUFFER_SIZE);
    sem_init(&full_count, 0, 0);

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to complete
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy synchronization primitives
    pthread_mutex_destroy(&lock);
    sem_destroy(&empty_count);
    sem_destroy(&full_count);

    return 0;
}
