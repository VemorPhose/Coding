#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>

int queue[] = {0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0};
int queue_size = sizeof(queue) / sizeof(queue[0]);

pthread_mutex_t mutex;
sem_t men_sem;
sem_t women_sem;
int count = 0;
int current_gender = -1;
int men_waiting = 0;
int women_waiting = 0;

void *woman_leaves(void *arg);
void *man_leaves(void *arg);

void *woman_wants_to_enter(void *arg) {
    int id = *((int *)arg);
    printf("Woman %d wants to enter.\n", id);

    pthread_mutex_lock(&mutex);

    if (current_gender == 0 || (current_gender == -1 && men_waiting > 0)) {
        women_waiting++;
        pthread_mutex_unlock(&mutex);
        sem_wait(&women_sem);
    } else {
         pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_lock(&mutex);

    if(women_waiting > 0 && current_gender != 0) {
        women_waiting--;
    }

    if (count == 0) {
        printf("Restroom occupied by women.\n\n");
        current_gender = 1;
    }

    count++;
    printf("Woman %d enters.\n", id);
    printf("Women inside: %d.\n", count);


    if (women_waiting > 0) {
        sem_post(&women_sem);
    }

    pthread_mutex_unlock(&mutex);

    pthread_t tid;
    int *leave_id = malloc(sizeof(int));
    if (!leave_id) { perror("Failed to allocate memory for leave_id"); exit(EXIT_FAILURE); }
    *leave_id = id;

    pthread_create(&tid, NULL, woman_leaves, leave_id);
    pthread_detach(tid);

    free(arg);

    return NULL;
}

void *man_wants_to_enter(void *arg) {
    int id = *((int *)arg);
    printf("Man %d wants to enter.\n", id);

    pthread_mutex_lock(&mutex);

    if (current_gender == 1 || (current_gender == -1 && women_waiting > 0)) {
        men_waiting++;
        pthread_mutex_unlock(&mutex);
        sem_wait(&men_sem);
    } else {
         pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_lock(&mutex);

    if(men_waiting > 0 && current_gender != 1) {
        men_waiting--;
    }

    if (count == 0) {
        printf("Restroom occupied by men.\n\n");
        current_gender = 0;
    }

    count++;
    printf("Man %d enters.\n", id);
    printf("Men inside: %d.\n", count);

    if (men_waiting > 0) {
        sem_post(&men_sem);
    }

    pthread_mutex_unlock(&mutex);

    pthread_t tid;
    int *leave_id = malloc(sizeof(int));
    if (!leave_id) { perror("Failed to allocate memory for leave_id"); exit(EXIT_FAILURE); }
    *leave_id = id;

    pthread_create(&tid, NULL, man_leaves, leave_id);
    pthread_detach(tid);

    free(arg);

    return NULL;
}


void *woman_leaves(void *arg) {
    int id = *((int *)arg);
    free(arg);

    pthread_mutex_lock(&mutex);
    count--;
    printf("Woman %d leaves.\n", id);
    printf("Women inside: %d.\n", count);

    bool signal_men = false;

    if (count == 0) {
        printf("Restroom empty.\n\n");
        current_gender = -1;
        if (men_waiting > 0) {
            signal_men = true;
        }
    }

    pthread_mutex_unlock(&mutex);

    if (signal_men) {
        sem_post(&men_sem);
    }

    return NULL;
}

void *man_leaves(void *arg) {
    int id = *((int *)arg);
    free(arg);

    pthread_mutex_lock(&mutex);
    count--;
    printf("Man %d leaves.\n", id);
    printf("Men inside: %d.\n", count);

    bool signal_women = false;

    if (count == 0) {
        printf("Restroom empty.\n\n");
        current_gender = -1;
        if (women_waiting > 0) {
             signal_women = true;
        }
    }

    pthread_mutex_unlock(&mutex);

    if (signal_women) {
        sem_post(&women_sem);
    }

    return NULL;
}


int main() {
    pthread_t threads[queue_size];

    pthread_mutex_init(&mutex, NULL);
    sem_init(&men_sem, 0, 0);
    sem_init(&women_sem, 0, 0);

    for (int i = 0; i < queue_size; i++) {
        int *id = malloc(sizeof(int));
         if (!id) { perror("Failed to allocate memory for thread ID"); exit(EXIT_FAILURE); }
        *id = i + 1;

        if (queue[i] == 0) {
            pthread_create(&threads[i], NULL, man_wants_to_enter, id);
        } else {
            pthread_create(&threads[i], NULL, woman_wants_to_enter, id);
        }
    }

    for (int i = 0; i < queue_size; i++) {
        pthread_join(threads[i], NULL);
    }
    sleep(2);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&men_sem);
    sem_destroy(&women_sem);

    return 0;
}