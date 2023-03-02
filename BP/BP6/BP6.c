#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char const *argv[]) {
    int id = fork();
    if (id == 0) {
        printf("Child process with pid %d\n", getpid());
        sleep(10);
        printf("Child process with pid %d is done\n", getpid());
        return 0;
    } else {
        printf("Parent process with pid %d\n", getpid());
        sleep(5);
        wait(NULL);
        printf("Parent process with pid %d is done\n", getpid());
        return 0;
    }
}
