#include <stdlib.h>
#include <stdio.h>

void printarr(int *array, int size) {
    printf("[");
    for(int i = 0; i < size - 1; i++)
        printf("%d, ", array[i]);
    printf("%d]\n", array[size - 1]);
}

int main() {
    // Allocating array of size 5 using malloc
    int *arr1 = (int *) malloc(sizeof(int) * 5);
    for(int i = 0; i < 5; i++) arr1[i] = i;
    printarr(arr1, 5);

    // increasing the size using realloc
    arr1 = (int *) realloc(arr1, sizeof(int) * 10);
    for(int i = 5; i < 10; i++) arr1[i] = i;
    printarr(arr1, 10);

    // Allocating array of size 10 using calloc
    // It Initialize all the values to 0 unlike malloc
    int *arr2 = (int *) calloc(10, sizeof(int));
    printarr(arr2, 10);

    // free(void *_ptr) is used to free the memory
    free(arr1);
    free(arr2);
}