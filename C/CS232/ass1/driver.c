#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t pid1, pid2;

    // Check arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
        exit(1);
    }

    // Open files
    int file1 = open(argv[1], O_RDONLY);
    int file2 = creat(argv[2], 0644);
    if (file1 == -1 || file2 == -1) {
        perror("Error opening files");
        exit(1);
    }

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    // First child (count)
    if ((pid1 = fork()) == 0) {
        // Redirect stdin to pipe read end
        dup2(pipefd[0], STDIN_FILENO);
        // Redirect stdout to file2
        dup2(file2, STDOUT_FILENO);
        // Close unused file descriptors
        close(pipefd[1]);
        close(file1);
        close(file2);
        execl("./count", "count", NULL);
        perror("execl 2");
        exit(1);
    }

    // Second child (convert)
    if ((pid2 = fork()) == 0) {
        // Redirect stdin to file1
        dup2(file1, STDIN_FILENO);
        // Redirect stdout to pipe write end
        dup2(pipefd[1], STDOUT_FILENO);
        // Close unused file descriptors
        close(pipefd[0]);
        close(file1);
        close(file2);
        execl("./convert", "convert", NULL);
        perror("execl convert");
        exit(1);
    }

    // Parent
    close(pipefd[0]);
    close(pipefd[1]);
    close(file1);
    close(file2);
    
    wait(NULL);
    wait(NULL);
    
    exit(0);
}