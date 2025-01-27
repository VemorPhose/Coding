#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    int status;
    
    // Create child process
    pid = fork();
    
    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        exit(1);
    }
    else if (pid == 0) {
        // Child process
        printf("Child executing ls -l\n");
        char *args[] = {"ls", "-l", NULL};
        execvp("ls", args);
        
        // If execvp returns, there was an error
        perror("execvp failed");
        exit(1);
    }
    else {
        // Parent process
        printf("Parent waiting for child (PID: %d)\n", pid);
        wait(&status);
        printf("Child completed\n");
    }
    
    return 0;
}