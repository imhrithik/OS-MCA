#include "hashTable.h"
#include <pthread.h>
#include <unistd.h>

#define SIZE 5
#define MAX_WRITE 2
#define MAX_READ 2
#define MAX_THREAD 4

hashTable* map;

int readcount = 0;
int semaphore_mutex = 1;
int semaphore_write = 1;
int rc;

void wait(int *semaphore) {
    while(*semaphore <= 0);
    *semaphore = *semaphore - 1;
}

void signal(int *semaphore) {
    *semaphore = *semaphore + 1;
}

void Write(long id) {
    int wait = rand() % 2 + 1;
    sleep(wait);
    int key = rand() % SIZE + 1;
    int value = rand() % 100 + 1;
    setHashTable(map, key, value);
    printf("Writer #%ld key %d with value %d \n", id, key, value);
}

void *Writer(void *threadid) {
    int write = 0;
    do {
        wait(&semaphore_write);
        Write((long)threadid);
        write++;
        signal(&semaphore_write);
        usleep(100);
    } while(write <= MAX_WRITE);
    pthread_exit(NULL);
}

void Read(long id) {
    int wait = rand() % 2 + 1;
    sleep(wait);
    int key = rand() % SIZE + 1;
    int value = lookupHashTable(map, key);
    printf("Reader #%ld key %d with value %d \n", id, key, value);
}

void *Reader(void *threadid) {
    int reads = 0;
    do {
        wait(&semaphore_mutex);
        readcount++;
        if(readcount == 1)
            wait(&semaphore_write);
        signal(&semaphore_mutex);
        Read((long)threadid);
        wait(&semaphore_mutex);
        reads++;
        readcount--;
        if(readcount == 0)
            signal(&semaphore_write);
        signal(&semaphore_mutex);
        usleep(100);
    } while(reads < MAX_READ);
    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    pthread_t threads[MAX_THREAD];
    map = newHashTable(SIZE);
    for(int i = 0; i < SIZE; i++)
        insertHashTable(map, i + 1, 1);

    for(int i = 0; i < MAX_THREAD / 2; i++)
        rc = pthread_create(&threads[i + MAX_THREAD / 2], NULL, Writer, (void *)(i + MAX_THREAD / 2));
    for(int i = 0; i < MAX_THREAD / 2; i++)
        rc = pthread_create(&threads[i], NULL, Reader, (void *)i);
    
    for(int i = 0; i < MAX_THREAD; i++)
        pthread_join(threads[i], NULL);
    freeHashTable(map);
    pthread_exit(NULL);
}