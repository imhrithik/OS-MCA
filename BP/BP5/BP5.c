#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {

    // Create a zombies process
    pid_t zombies_pid = fork();
    if (zombies_pid == 0) {
        // Child process
        printf("Child process (zombie) with pid %d\n", getpid());
        exit(0);
    } else {
        // Parent process
        printf("Parent process with pid %d\n", getpid());
        sleep(5);
        wait(NULL);
    }

    // Create an orphan process
    pid_t orphan_pid = fork();
    if (orphan_pid == 0) {
        // Child process
        printf("Child process (orphan) with pid %d\n", getpid());
        sleep(10);
    } else {
        // Parent process
        printf("Parent process with pid %d\n", getpid());
        exit(0);
    }

    return 0;
}
