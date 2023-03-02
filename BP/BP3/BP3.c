#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_LOOP 5

int buffer[BUFFER_SIZE];

int semaphore_mutex = 1;
int semaphore_empty = BUFFER_SIZE;
int semaphore_full = 0;
int in = 0, out = 0;

void Produce(int *item) {
    int wait = rand() % 2 + 1;
    sleep(wait);
    *item = rand() % 50000;
    printf("Produced item #%d \n", *item);
}

void Consume(int *item) {
    int wait = rand() % 2 + 1;
    sleep(wait);
    printf("Consumed item #%d \n", *item);
}

void wait(int *semaphore) {
    while(*semaphore <= 0);
    *semaphore = *semaphore - 1;
}

void signal(int *semaphore) {
    *semaphore = *semaphore + 1;
}

void *Producer(void *threadid) {
    printf("Producer is running \n");
    int item;
    for(int i = 0; i < MAX_LOOP; i++) {
        Produce(&item);
        wait(&semaphore_empty);
        wait(&semaphore_mutex);
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        signal(&semaphore_mutex);
        signal(&semaphore_full);
    }
    pthread_exit(NULL);
}

void *Consumer(void *threadid) {
    printf("Consumer is running \n");
    for(int i = 0; i < MAX_LOOP; i++) {
        wait(&semaphore_full);
        wait(&semaphore_mutex);
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        signal(&semaphore_mutex);
        signal(&semaphore_empty);
        Consume(&item);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t threads[2];
    int rc;

    rc = pthread_create(&threads[0], NULL, Producer, NULL);
    if (rc) {
        printf("ERROR; return code from pthread_create() is %d \n", rc);
        exit(-1);
    }

    rc = pthread_create(&threads[1], NULL, Consumer, NULL);
    if (rc) {
        printf("ERROR; return code from pthread_create() is %d \n", rc);
        exit(-1);
    }

    pthread_exit(NULL);
}