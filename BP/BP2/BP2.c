#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3
#define MAX 2

bool choosing[NUM_THREADS];
int number[NUM_THREADS];

void *Process(void *threadid) {
    int runs = 0;
    int myturn = (int)threadid;
    do {
        choosing[myturn] = true;
        int max = 0;
        for (int i = 0; i < NUM_THREADS; i++) {
            if (number[i] > max) {
                max = number[i];
            }
        }
        number[myturn] = max + 1;
        choosing[myturn] = false;
        for (int i = 0; i < NUM_THREADS; i++) {
            while (choosing[i]);
            while (number[i] != 0 && (number[i] < number[myturn] || (number[i] == number[myturn] && i < myturn)));
        }
        int wait = rand() % 5 + 1;
        printf("Thread %d is in critical section and will take %ds of time \n", myturn, wait);
        sleep(wait);
        printf("Thread %d is out of critical section \n", myturn);
        number[myturn] = 0;
        runs++;
    } while (runs < MAX);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    pthread_t threads[NUM_THREADS];
    int rc;

    for(int i = 0; i < NUM_THREADS; i++) {
        choosing[i] = false;
        number[i] = 0;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        rc = pthread_create(&threads[i], NULL, Process, (void *)i);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d \n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
