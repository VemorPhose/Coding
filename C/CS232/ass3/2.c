#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 100

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

typedef struct Queue {
    int items[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

bool isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, int value) {
    if (q->front == -1) 
        q->front = 0;
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->items[q->rear] = value;
}

int dequeue(Queue *q) {
    int value = q->items[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    }
    return value;
}

void round_robin_scheduling(Process *processes, int n, int quantum, 
                          char **gantt_chart, int *chart_size) {
    Queue ready_queue;
    initQueue(&ready_queue);
    *chart_size = 0;
    
    int current_time = 0;
    int completed = 0;
    
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    enqueue(&ready_queue, 0);
    
    while (completed < n) {
        int current_process = -1;
        
        if (!isEmpty(&ready_queue)) {
            current_process = dequeue(&ready_queue);
            
            int execution_time = (processes[current_process].remaining_time < quantum) ? 
                                processes[current_process].remaining_time : quantum;
            
            char *entry = (char*)malloc(20 * sizeof(char));
            sprintf(entry, "%s (%d-%d)", 
                    processes[current_process].id,
                    current_time,
                    current_time + execution_time);
            gantt_chart[*chart_size] = entry;
            (*chart_size)++;
            
            processes[current_process].remaining_time -= execution_time;
            current_time += execution_time;
            
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival_time <= current_time && 
                    processes[i].remaining_time > 0 && 
                    i != current_process && 
                    !processes[i].is_completed) {
                    bool already_in_queue = false;
                    for (int j = ready_queue.front; 
                         j <= ready_queue.rear && j != -1; j++) {
                        if (ready_queue.items[j] == i) {
                            already_in_queue = true;
                            break;
                        }
                    }
                    if (!already_in_queue) {
                        enqueue(&ready_queue, i);
                    }
                }
            }
            
            if (processes[current_process].remaining_time == 0) {
                processes[current_process].completion_time = current_time;
                processes[current_process].turnaround_time = 
                    processes[current_process].completion_time - 
                    processes[current_process].arrival_time;
                processes[current_process].waiting_time = 
                    processes[current_process].turnaround_time - 
                    processes[current_process].burst_time;
                processes[current_process].is_completed = true;
                completed++;
            } else {
                enqueue(&ready_queue, current_process);
            }
        } else {
            current_time++;
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival_time <= current_time && 
                    processes[i].remaining_time > 0 && 
                    !processes[i].is_completed) {
                    enqueue(&ready_queue, i);
                }
            }
        }
    }
}

void print_statistics(Process *processes, int n, char **gantt_chart, int chart_size) {
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
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
    
    printf("\nAverage Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("\n");
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &quantum);
    
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
    
    char **gantt_chart = (char**)malloc(n * 100 * sizeof(char*));
    int chart_size = 0;
    
    round_robin_scheduling(processes, n, quantum, gantt_chart, &chart_size);
    print_statistics(processes, n, gantt_chart, chart_size);
    
    for (int i = 0; i < chart_size; i++) {
        free(gantt_chart[i]);
    }
    free(gantt_chart);
    free(processes);
    
    return 0;
}