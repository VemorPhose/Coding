#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct Process {
    char id[5];
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool is_completed;
} Process;

void srtf_scheduling(Process *processes, int n, char **gantt_chart, int *chart_size) {
    *chart_size = 0;
    
    int current_time = 0;
    int completed = 0;
    int prev_process = -1;
    int start_time = 0;
    
    // Initialize remaining times
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    while (completed < n) {
        int shortest_job_idx = -1;
        int shortest_remaining = INT_MAX;
        
        // Find process with shortest remaining time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && 
                !processes[i].is_completed && 
                processes[i].remaining_time < shortest_remaining) {
                shortest_remaining = processes[i].remaining_time;
                shortest_job_idx = i;
            }
        }
        
        if (shortest_job_idx == -1) {
            // No process available, advance time
            current_time++;
            continue;
        }
        
        // Context switch detected, create Gantt chart entry
        if (prev_process != shortest_job_idx) {
            if (prev_process != -1) {
                char *entry = (char*)malloc(20 * sizeof(char));
                sprintf(entry, "%s (%d-%d)", 
                        processes[prev_process].id,
                        start_time,
                        current_time);
                gantt_chart[*chart_size] = entry;
                (*chart_size)++;
            }
            start_time = current_time;
            prev_process = shortest_job_idx;
        }
        
        // Execute the process for 1 time unit
        processes[shortest_job_idx].remaining_time--;
        current_time++;
        
        // Check if process completed
        if (processes[shortest_job_idx].remaining_time == 0) {
            processes[shortest_job_idx].completion_time = current_time;
            processes[shortest_job_idx].turnaround_time = 
                processes[shortest_job_idx].completion_time - 
                processes[shortest_job_idx].arrival_time;
            processes[shortest_job_idx].waiting_time = 
                processes[shortest_job_idx].turnaround_time - 
                processes[shortest_job_idx].burst_time;
            processes[shortest_job_idx].is_completed = true;
            completed++;
            
            // Add final entry for this process
            char *entry = (char*)malloc(20 * sizeof(char));
            sprintf(entry, "%s (%d-%d)", 
                    processes[shortest_job_idx].id,
                    start_time,
                    current_time);
            gantt_chart[*chart_size] = entry;
            (*chart_size)++;
            
            prev_process = -1;  // Reset for next process
        }
    }
}

void print_statistics(Process *processes, int n, char **gantt_chart, int chart_size) {
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    
    printf("\nProcess details:\n");
    printf("%-5s %-12s %-10s %-15s %-15s %-10s\n", 
           "ID", "Arrival Time", "Burst Time", "Completion Time", "Turnaround Time", "Waiting Time");
    
    for (int i = 0; i < n; i++) {
        printf("%-5s %-12d %-10d %-15d %-15d %-10d\n", 
               processes[i].id, 
               processes[i].arrival_time, 
               processes[i].burst_time, 
               processes[i].completion_time, 
               processes[i].turnaround_time, 
               processes[i].waiting_time);
        
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    
    printf("\nGantt Chart:\n");
    for (int i = 0; i < chart_size; i++) {
        printf("%s", gantt_chart[i]);
        if (i < chart_size - 1) {
            printf(" | ");
        }
    }
    
    printf("\n\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    Process *processes = (Process*)malloc(n * sizeof(Process));
    
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);
        printf("ID (e.g., P1): ");
        scanf("%s", processes[i].id);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].is_completed = false;
    }
    
    char **gantt_chart = (char**)malloc(n * n * sizeof(char*));  // May have more context switches
    int chart_size = 0;
    
    srtf_scheduling(processes, n, gantt_chart, &chart_size);
    print_statistics(processes, n, gantt_chart, chart_size);
    
    // Free allocated memory
    for (int i = 0; i < chart_size; i++) {
        free(gantt_chart[i]);
    }
    free(gantt_chart);
    free(processes);
    
    return 0;
}