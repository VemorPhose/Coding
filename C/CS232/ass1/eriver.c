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

void handler(int sig) {
    fprintf(stderr, "Alarm timeout - killing children\n");
    longjmp(env, 1);
}

int main(int argc, char *argv[]) {
    int pipefd[2];
    int file1 = STDIN_FILENO;
    int file2 = STDOUT_FILENO;
    char *n_arg = NULL;
    int arg_index = 1;
    int status;
    pid_t pid;

    signal(SIGALRM, handler);

    if (setjmp(env) != 0) {
        kill(child1_pid, SIGTERM);
        kill(child2_pid, SIGTERM);
        while ((pid = wait(&status)) > 0) {
            fprintf(stderr, "Killed child pid=%d\n", pid);
        }
        exit(1);
    }

    // Parse arguments
    if (argc > 1 && argv[1][0] == '-') {
        n_arg = argv[1];
        arg_index++;
    }

    // Handle file arguments
    if (arg_index < argc) {
        if ((file1 = open(argv[arg_index], O_RDONLY)) == -1) {
            perror("Cannot open input file");
            exit(1);
        }
        arg_index++;
    }

    if (arg_index < argc) {
        if ((file2 = creat(argv[arg_index], 0644)) == -1) {
            perror("Cannot create output file");
            close(file1);
            exit(1);
        }
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Fork count process
    if ((child1_pid = fork()) == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        dup2(file2, STDOUT_FILENO);
        if (n_arg)
            execl("./count", "count", n_arg, NULL);
        else
            execl("./count", "count", NULL);
        perror("execl count");
        exit(1);
    }

    // Fork convert process
    if ((child2_pid = fork()) == 0) {
        close(pipefd[0]);
        dup2(file1, STDIN_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        execl("./convert", "convert", NULL);
        perror("execl convert");
        exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    if (file1 != STDIN_FILENO) close(file1);
    if (file2 != STDOUT_FILENO) close(file2);

    alarm(15);
    
    while ((pid = wait(&status)) > 0) {
        fprintf(stderr, "child pid=%d reaped with exit status=%d\n",
                pid, WEXITSTATUS(status));
        if (pid == child1_pid && WEXITSTATUS(status) == 2) {
            kill(child2_pid, SIGTERM);
            wait(NULL);
            exit(1);
        }
    }
    
    alarm(0);
    exit(0);
}