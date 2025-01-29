#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void print_numbers(int child_id) {
    for(int i = 1; i <= 5; i++) {
        printf("Child %d: Number %d\n", child_id, i);
        sleep(1);  // Delay to show process interaction
    }
}

int main() {
    pid_t pid1, pid2;
    int status1, status2;

    // Create first child
    pid1 = fork();
    if (pid1 < 0) {
        perror("First fork failed");
        exit(1);
    }
    else if (pid1 == 0) {
        // First child process
        print_numbers(1);
        exit(0);
    }

    // Create second child
    pid2 = fork();
    if (pid2 < 0) {
        perror("Second fork failed");
        exit(1);
    }
    else if (pid2 == 0) {
        // Second child process
        print_numbers(2);
        exit(0);
    }

    // Parent process waits for both children
    printf("Parent waiting for children to complete...\n");
    
    waitpid(pid1, &status1, 0);
    printf("Child 1 (PID: %d) completed\n", pid1);
    
    waitpid(pid2, &status2, 0);
    printf("Child 2 (PID: %d) completed\n", pid2);
    
    printf("All children completed\n");
    return 0;
}