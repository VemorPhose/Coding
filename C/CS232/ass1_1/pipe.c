#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char message[] = "Hello from parent!";
    char buffer[100];
    
    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    
    // Create child process
    pid = fork();
    
    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    else if (pid > 0) {
        // Parent process
        close(pipefd[0]);  // Close read end
        
        write(pipefd[1], message, strlen(message) + 1);
        printf("Parent wrote: %s\n", message);
        
        close(pipefd[1]);  // Close write end
        wait(NULL);  // Wait for child
    }
    else {
        // Child process
        close(pipefd[1]);  // Close write end
        
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child read: %s\n", buffer);
        
        close(pipefd[0]);  // Close read end
    }
    
    return 0;
}