#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct hashTable hashTable;

struct hashTable {
    int size;
    int *keys;
    int *values;
};

hashTable* newHashTable(int size) {
    hashTable* ht = (hashTable*) malloc(sizeof(struct hashTable));
    assert(ht != NULL);
    ht->size = size;
    ht->keys = (int *) malloc(size * sizeof(int));
    assert(ht->keys != NULL);
    ht->values = (int *) malloc(size * sizeof(int));
    assert(ht->values != NULL);
    return ht;
}

void freeHashTable(hashTable* ht) {
    free(ht->keys);
    free(ht->values);
    free(ht);
}

void insertHashTable(hashTable* ht, int key, int value) {
    int i = 0;
    while (i < ht->size && ht->keys[i] != 0) {
        if (ht->keys[i] == key) {
            ht->values[i] = value;
            return;
        }
        i++;
    }
    if (i == ht->size) {
        printf("Hash table is full \n");
        return;
    }
    ht->keys[i] = key;
    ht->values[i] = value;
}

int lookupHashTable(hashTable* ht, int key) {
    int i = 0;
    while (i < ht->size && ht->keys[i] != 0) {
        if (ht->keys[i] == key) {
            return ht->values[i];
        }
        i++;
    }
    printf("Key not found \n");
    return 0;
}

void deleteHashTable(hashTable* ht, int key) {
    int i = 0;
    while (i < ht->size && ht->keys[i] != 0) {
        if (ht->keys[i] == key) {
            ht->keys[i] = 0;
            ht->values[i] = 0;
            return;
        }
        i++;
    }
    printf("Key not found \n");
}

bool inHashTable(hashTable* ht, int key) {
    int i = 0;
    while (i < ht->size && ht->keys[i] != 0) {
        if (ht->keys[i] == key) {
            return true;
        }
        i++;
    }
    return false;
}

void setHashTable(hashTable* ht, int key, int value) {
    int i = 0;
    while (i < ht->size && ht->keys[i] != 0) {
        if (ht->keys[i] == key) {
            ht->values[i] = value;
            return;
        }
        i++;
    }
    printf("Key not found \n");
}

#endif