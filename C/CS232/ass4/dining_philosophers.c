#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define NUM_MEALS 3  // Number of times each philosopher will eat

// Mutex for each fork
pthread_mutex_t forks[NUM_PHILOSOPHERS];
// Track philosopher states for debugging
int state[NUM_PHILOSOPHERS]; // 0=thinking, 1=hungry, 2=eating

// Philosopher function
void *philosopher(void *arg) {
    int id = *((int *)arg);
    free(arg);
    
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;
    
    // To prevent deadlock, even philosophers pick right fork first,
    // odd philosophers pick left fork first
    int first_fork, second_fork;
    if (id % 2 == 0) {
        first_fork = right_fork;
        second_fork = left_fork;
    } else {
        first_fork = left_fork;
        second_fork = right_fork;
    }
    
    for (int i = 0; i < NUM_MEALS; i++) {
        // Thinking
        printf("Philosopher %d is thinking\n", id);
        state[id] = 0;
        sleep(rand() % 3);
        
        // Hungry
        printf("Philosopher %d is hungry\n", id);
        state[id] = 1;
        
        // Pick up forks
        pthread_mutex_lock(&forks[first_fork]);
        printf("Philosopher %d picked up fork %d\n", id, first_fork);
        pthread_mutex_lock(&forks[second_fork]);
        printf("Philosopher %d picked up fork %d\n", id, second_fork);
        
        // Eating
        printf("Philosopher %d is eating (meal %d)\n", id, i+1);
        state[id] = 2;
        sleep(rand() % 3);
        
        // Put down forks
        pthread_mutex_unlock(&forks[second_fork]);
        printf("Philosopher %d put down fork %d\n", id, second_fork);
        pthread_mutex_unlock(&forks[first_fork]);
        printf("Philosopher %d put down fork %d\n", id, first_fork);
    }
    
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    
    // Initialize mutexes for forks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
        state[i] = 0; // All philosophers start thinking
    }
    
    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&philosophers[i], NULL, philosopher, id);
    }
    
    // Wait for philosophers to finish
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    // Destroy mutexes
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    
    return 0;
}