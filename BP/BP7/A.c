#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        char *args[] = {"./B.o", "1", "10", NULL};
        execvp(args[0], args);
    } else {
        // Parent process
        wait(NULL);
    }
    return 0;
}