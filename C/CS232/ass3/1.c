#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INF 999999

typedef struct Process {
    char id[5];
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    bool is_completed;
} Process;

void print_statistics(Process *processes, int n, char **gantt_chart, int chart_size) {
    printf("\nGantt Chart:\n");
    for (int i = 0; i < chart_size; i++) {
        printf("%s", gantt_chart[i]);
        if (i < chart_size - 1) {
            printf(" | ");
        }
    }
    
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += processes[i].waiting_time;
        avg_turnaround_time += processes[i].turnaround_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("\nAvg. Waiting Time: %.2f\n", avg_waiting_time);
    printf("Avg. Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("\n");
}

void sjf_scheduling(Process *processes, int n, char **gantt_chart, int *chart_size) {
    int current_time = 0;
    int completed = 0;

    while (completed < n) {
        int shortest_job_idx = -1;
        int shortest_burst = INF;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && 
                !processes[i].is_completed) {
                if (processes[i].burst_time < shortest_burst) {
                    shortest_burst = processes[i].burst_time;
                    shortest_job_idx = i;
                }
            }
        }
        
        if (shortest_job_idx == -1) {
            current_time++;
            continue;
        }

        processes[shortest_job_idx].completion_time = 
            current_time + processes[shortest_job_idx].burst_time;
        processes[shortest_job_idx].turnaround_time = 
            processes[shortest_job_idx].completion_time - 
            processes[shortest_job_idx].arrival_time;
        processes[shortest_job_idx].waiting_time = 
            processes[shortest_job_idx].turnaround_time - 
            processes[shortest_job_idx].burst_time;
        processes[shortest_job_idx].is_completed = true;
        
        char *entry = (char*)malloc(20 * sizeof(char));
        sprintf(entry, "%s (%d-%d)", 
                processes[shortest_job_idx].id,
                current_time,
                processes[shortest_job_idx].completion_time);
        gantt_chart[*chart_size] = entry;
        (*chart_size)++;
        
        current_time = processes[shortest_job_idx].completion_time;
        completed++;
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    Process *processes = (Process*) malloc(n * sizeof(Process));
    
    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i + 1);
        printf("ID (e.g., P1): ");
        scanf("%s", processes[i].id);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].is_completed = 0;
    }
    
    char **gantt_chart = (char**) malloc(n * sizeof(char*));
    int chart_size = 0;

    sjf_scheduling(processes, n, gantt_chart, &chart_size);
    print_statistics(processes, n, gantt_chart, chart_size);
    
    for (int i = 0; i < chart_size; i++) {
        free(gantt_chart[i]);
    }
    free(gantt_chart);
    free(processes);
    return 0;
}