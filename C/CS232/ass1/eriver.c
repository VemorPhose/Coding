#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <setjmp.h>
#include <string.h>

static jmp_buf env;
static pid_t child1_pid, child2_pid;

void alarm_handler(int sig) {
    longjmp(env, 1);
}

int main(int argc, char *argv[]) {
    int pipefd[2];
    int file1 = STDIN_FILENO;
    int file2 = STDOUT_FILENO;
    char *n_arg = NULL;
    int arg_index = 1;

    // Parse arguments
    if (argc > 1 && argv[1][0] == '-') {
        n_arg = argv[1];
        arg_index++;
    }
    
    // Handle file arguments
    if (arg_index < argc) {
        file1 = open(argv[arg_index], O_RDONLY);
        if (file1 == -1) {
            perror("open");
            exit(1);
        }
        arg_index++;
    }
    
    if (arg_index < argc) {
        file2 = creat(argv[arg_index], 0644);
        if (file2 == -1) {
            perror("creat");
            close(file1);
            exit(1);
        }
    }

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        if (file1 != STDIN_FILENO) close(file1);
        if (file2 != STDOUT_FILENO) close(file2);
        exit(1);
    }

    // Set up signal handler for alarm
    signal(SIGALRM, alarm_handler);

    // First child (count)
    if ((child1_pid = fork()) == 0) {
        fprintf(stderr, "Count process PID: %d\n", getpid());
        dup2(pipefd[0], STDIN_FILENO);
        dup2(file2, STDOUT_FILENO);
        close(pipefd[1]);
        close(file1);
        close(file2);
        
        if (n_arg)
            execl("./count", "count", n_arg, NULL);
        else
            execl("./count", "count", NULL);
            
        perror("execl count");
        exit(1);
    }

    // Second child (convert)
    if ((child2_pid = fork()) == 0) {
        fprintf(stderr, "Convert process PID: %d\n", getpid());
        dup2(file1, STDIN_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(file1);
        close(file2);
        execl("./convert", "convert", NULL);
        perror("execl convert");
        exit(1);
    }

    // Parent process
    close(pipefd[0]);
    close(pipefd[1]);
    if (file1 != STDIN_FILENO) close(file1);
    if (file2 != STDOUT_FILENO) close(file2);

    // Set up setjmp for alarm handling
    if (setjmp(env) == 0) {
        alarm(15);  // Set 15 second alarm
        
        int status;
        pid_t pid;
        while ((pid = wait(&status)) > 0) {
            if (WIFEXITED(status)) {
                if (WEXITSTATUS(status) == 2) {
                    fprintf(stderr, "Child %d exited with error\n", pid);
                    kill(pid == child1_pid ? child2_pid : child1_pid, SIGTERM);
                    wait(NULL);
                    exit(1);
                }
            }
        }
        
        alarm(0);  // Cancel alarm
        fprintf(stderr, "Normal children exit\n");
        exit(0);
    } else {
        // Alarm went off
        fprintf(stderr, "Read timeout, killing both children\n");
        kill(child1_pid, SIGTERM);
        kill(child2_pid, SIGTERM);
        wait(NULL);
        wait(NULL);
        exit(1);
    }
}