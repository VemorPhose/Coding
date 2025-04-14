#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_CAPACITY 10
#define MAX_WAITING 5

// 0 is man, 1 is woman.
int queue[] = {0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1};
int queue_size = sizeof(queue) / sizeof(queue[0]);
int *status;  // 0 = waiting, 1 = served, 2 = currently in restroom
int first_waiting = 1;

pthread_mutex_t mutex;
sem_t men, women;
int count = 0;

void find_first_waiting()
{
    pthread_mutex_lock(&mutex);
    int old_first = first_waiting;
    
    // Skip over people who have already been served
    for (int i = 0; i < queue_size; i++)
    {
        if (status[i] == 0)  // Found someone still waiting
        {
            first_waiting = i + 1;
            break;
        }
    }
    
    // If we've gone through everyone, point beyond the array
    if (old_first == first_waiting) {
        first_waiting = queue_size + 1;
    }
    
    pthread_mutex_unlock(&mutex);
}

void *woman_leaves(void *arg)
{
    int id = *((int *)arg);
    free(arg);
    
    pthread_mutex_lock(&mutex);
    sem_post(&women);
    count -= 1;
    printf("Woman %d leaves.\n", id);
    printf("Women inside: %d.\n", count);
    status[id - 1] = 1;  // Mark as served
    
    if (count == 0)
    {
        printf("Restroom empty.\n\n");
        for (int i = 0; i < MAX_CAPACITY; i++)
        {
            sem_post(&men);
        }
    }
    pthread_mutex_unlock(&mutex);
    
    find_first_waiting();
    return NULL;
}

void *man_leaves(void *arg)
{
    int id = *((int *)arg);
    free(arg);
    
    pthread_mutex_lock(&mutex);
    sem_post(&men);
    count -= 1;
    printf("Man %d leaves.\n", id);
    printf("Men inside: %d.\n", count);
    status[id - 1] = 1;  // Mark as served
    
    if (count == 0)
    {
        printf("Restroom empty.\n\n");
        for (int i = 0; i < MAX_CAPACITY; i++)
        {
            sem_post(&women);
        }
    }
    pthread_mutex_unlock(&mutex);
    
    find_first_waiting();
    return NULL;
}

void *woman_wants_to_enter(void *arg)
{
    int id = *((int *)arg);
    printf("Woman %d wants to enter.\n", id);
    
    // Check starvation avoidance with proper synchronization
    int can_proceed = 0;
    while (!can_proceed) {
        pthread_mutex_lock(&mutex);
        if (id - first_waiting < MAX_WAITING) {
            can_proceed = 1;
            status[id - 1] = 2;  // Mark as currently in restroom
        } else {
            printf("Woman %d waiting due to starvation control.\n", id);
        }
        pthread_mutex_unlock(&mutex);
        
        if (!can_proceed) {
            // More efficient sleep that doesn't block everything
            usleep(100000);  // 100ms instead of 1s for more responsiveness
            // Don't check as frequently to reduce contention
        }
    }
    
    sem_wait(&women);
    pthread_mutex_lock(&mutex);
    if (count == 0)
    {
        printf("Restroom occupied by women.\n\n");
        for (int i = 0; i < MAX_CAPACITY; i++)
        {
            sem_wait(&men);
        }
    }
    count += 1;
    printf("Woman %d enters.\n", id);
    printf("Women inside: %d.\n", count);
    pthread_mutex_unlock(&mutex);

    pthread_t tid;
    pthread_create(&tid, NULL, woman_leaves, arg);
    pthread_join(tid, NULL);
    return NULL;
}

void *man_wants_to_enter(void *arg)
{
    int id = *((int *)arg);
    printf("Man %d wants to enter.\n", id);
    
    // Check starvation avoidance with proper synchronization
    int can_proceed = 0;
    while (!can_proceed) {
        pthread_mutex_lock(&mutex);
        if (id - first_waiting < MAX_WAITING) {
            can_proceed = 1;
            status[id - 1] = 2;  // Mark as currently in restroom
        } else {
            printf("Man %d waiting due to starvation control.\n", id);
        }
        pthread_mutex_unlock(&mutex);
        
        if (!can_proceed) {
            // More efficient sleep that doesn't block everything
            usleep(100000);  // 100ms instead of 1s for more responsiveness
            // Don't check as frequently to reduce contention
        }
    }
    
    sem_wait(&men);
    pthread_mutex_lock(&mutex);
    if (count == 0)
    {
        printf("Restroom occupied by men.\n\n");
        for (int i = 0; i < MAX_CAPACITY; i++)
        {
            sem_wait(&women);
        }
    }
    count += 1;
    printf("Man %d enters.\n", id);
    printf("Men inside: %d.\n", count);
    pthread_mutex_unlock(&mutex);

    pthread_t tid;
    pthread_create(&tid, NULL, man_leaves, arg);
    pthread_join(tid, NULL);
    return NULL;
}

int main()
{
    status = calloc(queue_size, sizeof(int));
    for (int i = 0; i < queue_size; i++)
        status[i] = 0;
    pthread_t threads[queue_size];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&men, 0, MAX_CAPACITY);
    sem_init(&women, 0, MAX_CAPACITY);

    for (int i = 0; i < queue_size; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&threads[i], NULL,
                       queue[i] == 0 ? man_wants_to_enter : woman_wants_to_enter,
                       id);
        // Small delay to make output more readable
        usleep(50000);
    }
    
    for (int i = 0; i < queue_size; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
    pthread_mutex_destroy(&mutex);
    sem_destroy(&men);
    sem_destroy(&women);
    free(status);

    return 0;
}