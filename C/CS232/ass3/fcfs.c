#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Process {
    char id[5];
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool is_completed;
} Process;

void fcfs_scheduling(Process *processes, int n, char **gantt_chart, int *chart_size) {
    *chart_size = 0;
    int current_time = 0;
    
    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        // If CPU is idle, move time to next arrival
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        
        // Create Gantt chart entry
        char *entry = (char*)malloc(20 * sizeof(char));
        sprintf(entry, "%s (%d-%d)", 
                processes[i].id,
                current_time,
                current_time + processes[i].burst_time);
        gantt_chart[*chart_size] = entry;
        (*chart_size)++;
        
        // Calculate metrics
        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        processes[i].is_completed = true;
        
        // Update current time
        current_time = processes[i].completion_time;
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
    
    char **gantt_chart = (char**)malloc(n * sizeof(char*));
    int chart_size = 0;
    
    fcfs_scheduling(processes, n, gantt_chart, &chart_size);
    print_statistics(processes, n, gantt_chart, chart_size);
    
    // Free allocated memory
    for (int i = 0; i < chart_size; i++) {
        free(gantt_chart[i]);
    }
    free(gantt_chart);
    free(processes);
    
    return 0;
}