#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child_pids[3];
    FILE *file;
    char line[100];

    // Open the file
    file = fopen("courses.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Fork child processes
    for (int i = 0; i < 3; i++) {
        fgets(line, sizeof(line), file);
        child_pids[i] = fork();
        if (child_pids[i] == 0) {
            // Child process
            printf("Child %d: %s", i+1, line);
            exit(0);
        }
    }

    // Wait for child processes to finish
    for (int i = 0; i < 3; i++) {
        waitpid(child_pids[i], NULL, 0);
    }

    // Close the file
    fclose(file);

    return 0;
}