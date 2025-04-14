#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

// Structure to store the results of each algorithm
typedef struct {
    int* sequence;        // Order of serviced requests
    int total_seek_time;  // Total head movement
    double avg_seek_time; // Average seek time
} Result;

// Function prototypes
Result fcfs(int* requests, int n, int initial_head);
Result sstf(int* requests, int n, int initial_head);
Result scan(int* requests, int n, int initial_head, int disk_size);
void print_result(const char* algorithm_name, Result result, int n);
void free_result(Result result);

int main() {
    int disk_size, initial_head, n;
    
    // Get disk parameters
    printf("Enter disk size (number of cylinders): ");
    scanf("%d", &disk_size);
    
    printf("Enter initial head position: ");
    scanf("%d", &initial_head);
    
    printf("Enter number of requests: ");
    scanf("%d", &n);
    
    int* requests = (int*)malloc(n * sizeof(int));
    if (!requests) {
        perror("Memory allocation failed");
        return 1;
    }
    
    printf("Enter request queue (cylinder numbers):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requests[i]);
        if (requests[i] >= disk_size) {
            printf("Warning: Request %d exceeds disk size, capping at %d\n", requests[i], disk_size - 1);
            requests[i] = disk_size - 1;
        }
    }
    
    // Run all algorithms
    Result result_fcfs = fcfs(requests, n, initial_head);
    Result result_sstf = sstf(requests, n, initial_head);
    Result result_scan = scan(requests, n, initial_head, disk_size);
    
    // Print results
    printf("\n");
    print_result("FCFS", result_fcfs, n);
    print_result("SSTF", result_sstf, n);
    print_result("SCAN", result_scan, n);
    
    // Free memory
    free(requests);
    free_result(result_fcfs);
    free_result(result_sstf);
    free_result(result_scan);
    
    return 0;
}

// First-Come, First-Served (FCFS) algorithm
Result fcfs(int* requests, int n, int initial_head) {
    Result result;
    result.sequence = (int*)malloc(n * sizeof(int));
    result.total_seek_time = 0;
    
    if (!result.sequence) {
        perror("Memory allocation failed");
        exit(1);
    }
    
    int current_head = initial_head;
    
    for (int i = 0; i < n; i++) {
        result.sequence[i] = requests[i];
        result.total_seek_time += abs(current_head - requests[i]);
        current_head = requests[i];
    }
    
    result.avg_seek_time = (double)result.total_seek_time / n;
    return result;
}

// Shortest Seek Time First (SSTF) algorithm
Result sstf(int* requests, int n, int initial_head) {
    Result result;
    result.sequence = (int*)malloc(n * sizeof(int));
    result.total_seek_time = 0;
    
    if (!result.sequence) {
        perror("Memory allocation failed");
        exit(1);
    }
    
    bool* visited = (bool*)calloc(n, sizeof(bool));
    if (!visited) {
        perror("Memory allocation failed");
        free(result.sequence);
        exit(1);
    }
    
    int current_head = initial_head;
    
    for (int i = 0; i < n; i++) {
        int min_distance = INT_MAX;
        int min_index = -1;
        
        // Find the closest request
        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int distance = abs(current_head - requests[j]);
                if (distance < min_distance) {
                    min_distance = distance;
                    min_index = j;
                }
            }
        }
        
        // Mark as visited and update head position
        visited[min_index] = true;
        result.sequence[i] = requests[min_index];
        result.total_seek_time += min_distance;
        current_head = requests[min_index];
    }
    
    result.avg_seek_time = (double)result.total_seek_time / n;
    free(visited);
    return result;
}

// SCAN (Elevator) algorithm
Result scan(int* requests, int n, int initial_head, int disk_size) {
    Result result;
    result.sequence = (int*)malloc(n * sizeof(int));
    result.total_seek_time = 0;
    
    if (!result.sequence) {
        perror("Memory allocation failed");
        exit(1);
    }
    
    // Create a copy of requests with initial head for sorting
    int total_points = n + 1;  // requests + initial head
    int* positions = (int*)malloc(total_points * sizeof(int));
    
    if (!positions) {
        perror("Memory allocation failed");
        free(result.sequence);
        exit(1);
    }
    
    positions[0] = initial_head;
    for (int i = 0; i < n; i++) {
        positions[i + 1] = requests[i];
    }
    
    // Sort positions
    for (int i = 0; i < total_points; i++) {
        for (int j = i + 1; j < total_points; j++) {
            if (positions[i] > positions[j]) {
                int temp = positions[i];
                positions[i] = positions[j];
                positions[j] = temp;
            }
        }
    }
    
    // Find the position of initial head in the sorted array
    int head_index = 0;
    for (int i = 0; i < total_points; i++) {
        if (positions[i] == initial_head) {
            head_index = i;
            break;
        }
    }
    
    // Direction: initially move toward higher cylinder numbers (right/up)
    int current_head = initial_head;
    int sequence_index = 0;
    
    // First move right (up) to the end of disk
    for (int i = head_index + 1; i < total_points; i++) {
        if (positions[i] != initial_head) {  // Skip the initial head in the sequence
            result.sequence[sequence_index++] = positions[i];
            result.total_seek_time += abs(current_head - positions[i]);
            current_head = positions[i];
        }
    }
    
    // Then move left (down) to start of disk
    if (current_head < disk_size - 1) {
        // If we didn't reach the end of the disk, add the movement to the end
        result.total_seek_time += abs(current_head - (disk_size - 1));
        current_head = disk_size - 1;
    }
    
    for (int i = head_index - 1; i >= 0; i--) {
        result.sequence[sequence_index++] = positions[i];
        result.total_seek_time += abs(current_head - positions[i]);
        current_head = positions[i];
    }
    
    result.avg_seek_time = (double)result.total_seek_time / n;
    free(positions);
    return result;
}

// Print the results of an algorithm
void print_result(const char* algorithm_name, Result result, int n) {
    printf("--- %s Algorithm ---\n", algorithm_name);
    
    printf("Sequence of serviced requests: ");
    for (int i = 0; i < n; i++) {
        printf("%d", result.sequence[i]);
        if (i < n - 1) printf(", ");
    }
    printf("\n");
    
    printf("Total seek time: %d\n", result.total_seek_time);
    printf("Average seek time: %.2f\n\n", result.avg_seek_time);
}

// Free memory allocated for a result
void free_result(Result result) {
    free(result.sequence);
}