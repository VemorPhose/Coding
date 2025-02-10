#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5
#define ARRAY_SIZE 1000000

// Structure for thread data
struct thread_data {
    int thread_id;
    int* array;
    int start_index;
    int end_index;
    long long partial_sum;
};

// Thread function
void* t_runner(void* arg) {
    struct thread_data *my_data = (struct thread_data*) arg;
    my_data->partial_sum = 0;
    
    // Calculate sum for this thread's chunk
    for(int i = my_data->start_index; i < my_data->end_index; i++) {
        my_data->partial_sum += my_data->array[i];
    }
    
    printf("Thread %d: Partial sum = %lld\n", 
           my_data->thread_id, 
           my_data->partial_sum);
           
    pthread_exit(0);
}

int main() {
    // Thread IDs array
    pthread_t tid[NUM_THREADS];
    
    // Create attributes
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    // Create and initialize array
    int* array = (int*)malloc(ARRAY_SIZE * sizeof(int));
    for(int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;  // Fill with 1 to ARRAY_SIZE
    }
    
    // Create thread data array
    struct thread_data thread_data_array[NUM_THREADS];
    int chunk_size = ARRAY_SIZE / NUM_THREADS;
    
    // Create multiple threads
    for(int i = 0; i < NUM_THREADS; i++) {
        thread_data_array[i].thread_id = i;
        thread_data_array[i].array = array;
        thread_data_array[i].start_index = i * chunk_size;
        thread_data_array[i].end_index = (i == NUM_THREADS - 1) ? 
                                       ARRAY_SIZE : 
                                       (i + 1) * chunk_size;
        
        printf("Creating thread %d\n", i);
        pthread_create(&tid[i], &attr, t_runner, 
                      (void*)&thread_data_array[i]);
    }
    
    // Wait for all threads to complete and sum their results
    long long total_sum = 0;
    for(int i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
        total_sum += thread_data_array[i].partial_sum;
    }
    
    printf("Total sum: %lld\n", total_sum);
    
    // Clean up
    free(array);
    return 0;
}