#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 3

int readcount = 0;
pthread_mutex_t mutex;
sem_t wrt;

void *reader(void *arg) {
    int id = *((int *)arg);
    free(arg);
    while (1) {
        pthread_mutex_lock(&mutex);
        readcount++;
        if (readcount == 1) {
            sem_wait(&wrt);
        }
        pthread_mutex_unlock(&mutex);

        printf("Reader %d is reading\n", id);
        sleep(1);

        pthread_mutex_lock(&mutex);
        readcount--;
        if (readcount == 0) {
            sem_post(&wrt);
        }
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *((int *)arg);
    free(arg);
    while (1) {
        sem_wait(&wrt);

        printf("Writer %d is writing\n", id);
        sleep(1);

        sem_post(&wrt);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    for (int i = 0; i < NUM_READERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&readers[i], NULL, reader, id);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&writers[i], NULL, writer, id);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}