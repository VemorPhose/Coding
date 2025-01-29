#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;
    int stdout_copy;
    
    // Open output file
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    
    // Save copy of stdout
    stdout_copy = dup(STDOUT_FILENO);
    if (stdout_copy == -1) {
        perror("dup");
        exit(1);
    }
    
    // Redirect stdout to file
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(1);
    }
    
    // Write message (goes to file)
    printf("This will be written to the file.\n");
    fflush(stdout);
    
    // Restore original stdout
    if (dup2(stdout_copy, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(1);
    }
    
    // Clean up
    close(fd);
    close(stdout_copy);
    
    printf("Program completed.\n");  // This prints to terminal
    return 0;
}