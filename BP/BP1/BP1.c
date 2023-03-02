#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

bool flag[2] = {false, false};
int turn;

void *Process (void *threadid) {
    int wait = rand() % 5 + 1;
    sleep(wait);
    long myturn;
    myturn = (long)threadid;
    long other = (myturn + 1) % 2;
    flag[myturn] = true;
    turn = other;
    while (flag[other] && turn == other);
    wait = rand() % 5 + 1;
    printf("Thread %ld is in critical section and will take %ds of time \n", myturn, wait);
    sleep(wait);
    printf("Thread %ld is out of critical section \n", myturn);
    flag[myturn] = false;
    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    // Peterson algorithm
    pthread_t threads[2];
    int rc;
    int i;
    for (i = 0; i < 2; i++) {
        printf("In main: creating thread %d \n", i);
        rc = pthread_create(&threads[i], NULL, Process, (void *)i);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d \n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
