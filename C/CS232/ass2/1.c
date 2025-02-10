#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

// Structure for thread data
struct thread_data {
    int thread_id;
    char *message;
};

// Thread function
void* t_runner(void* arg) {
    struct thread_data *my_data = (struct thread_data*) arg;
    printf("Thread ID: %d, Message: %s from thread\n", 
           my_data->thread_id, 
           my_data->message);
    pthread_exit(0);
}

int main() {
    // Thread IDs array
    pthread_t tid[NUM_THREADS];
    
    // Create attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    // Create thread data array
    struct thread_data thread_data_array[NUM_THREADS];
    
    // Create multiple threads
    for(int i = 0; i < NUM_THREADS; i++) {
        thread_data_array[i].thread_id = i;
        thread_data_array[i].message = "Hello";
        
        printf("Creating thread %d\n", i);
        pthread_create(&tid[i], &attr, t_runner, 
                      (void*)&thread_data_array[i]);
    }
    
    // Wait for all threads to complete
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }
    
    printf("Back to main thread\n");
    return 0;
}

