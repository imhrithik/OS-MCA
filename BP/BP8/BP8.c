#include <stdio.h>
#include <stdlib.h>

int main() {
    // Use malloc() to allocate memory for an integer
    int *ptr1 = (int *) malloc(sizeof(int));
    *ptr1 = 10;
    printf("Value at ptr1: %d\n", *ptr1);

    // Use calloc() to allocate memory for an array of 5 integers
    int *ptr2 = (int *) calloc(5, sizeof(int));
    for (int i = 0; i < 5; i++) {
        ptr2[i] = i + 1;
    }
    printf("Values at ptr2: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", ptr2[i]);
    }
    printf("\n");

    // Use realloc() to change the size of the memory allocated for ptr2
    ptr2 = (int *) realloc(ptr2, 10 * sizeof(int));
    for (int i = 5; i < 10; i++) {
        ptr2[i] = i + 1;
    }
    printf("Values after realloc at ptr2: ");
    for (int i = 0; i < 10; i++) {
        printf("%d ", ptr2[i]);
    }
    printf("\n");

    // Use free() to deallocate memory
    free(ptr1);
    free(ptr2);

    return 0;
}
