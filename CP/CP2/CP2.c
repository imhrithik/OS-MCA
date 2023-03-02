#include <stdlib.h>
#include <stdio.h>

void printarr(int *array, int size) {
    printf("[");
    for(int i = 0; i < size - 1; i++)
        printf("%d, ", array[i]);
    printf("%d]\n", array[size - 1]);
}

int main() {
    int n;
    int *array = (int *) malloc(n * sizeof(int));
    FILE *file, *fileOdd, *fileEven;
    int *arrayOdd, *arrayEven;

    printf("Enter the number n: ");
    scanf("%d", &n);


    for (int i = 1; i <= n; i++) {
        array[i - 1] = i;
    }

    // Writing Integers to the file
    file = fopen("All.txt", "wb");
    fwrite(array, sizeof(int), n, file);
    fclose(file);

    free(array);

    // Reading Integers from the file
    file = fopen("All.txt", "rb");

    // Getting file size
    fseek(file, 0L, SEEK_END);
    long int s1 = ftell(file) / sizeof(int);
    fseek(file, 0L, SEEK_SET);

    // Reading file
    array = (int *)calloc(sizeof(int), s1);
    fread(array, sizeof(int), s1, file);
    printf("Contents of All.txt: ");
    printarr(array, s1);

    fclose(file);

    // Writing to fileOdd and fileEven
    fileOdd = fopen("Odd.txt", "wb+");
    fileEven = fopen("Even.txt", "wb+");

    for (int i = 0; i < s1; i++)
        if (array[i] % 2 == 1)
            fwrite(&array[i], sizeof(int), 1, fileOdd);
        else
            fwrite(&array[i], sizeof(int), 1, fileEven);

    free(array);
    fclose(fileEven);
    fclose(fileOdd);

    // Reading from fileOdd
    fileOdd = fopen("Odd.txt", "rb");

    fseek(fileOdd, 0L, SEEK_END);
    long int s2 = ftell(fileOdd) / sizeof(int);
    fseek(fileOdd, 0L, SEEK_SET);

    arrayOdd = (int *)calloc(sizeof(int), s2);
    fread(arrayOdd, sizeof(int), s2, fileOdd);
    printf("Contents of odd.txt: ");
    printarr(arrayOdd, s2);

    free(arrayOdd);
    
    fclose(fileOdd);

    // Reading from fileEven
    fileEven = fopen("Even.txt", "rb");

    fseek(fileEven, 0L, SEEK_END);
    long int s3 = ftell(fileEven) / sizeof(int);
    fseek(fileEven, 0L, SEEK_SET);

    arrayEven = (int *)calloc(sizeof(int), s3);
    fread(arrayEven, sizeof(int), s3, fileEven);
    printf("Contents of even.txt: ");
    printarr(arrayEven, s3);

    free(arrayEven);
    
    fclose(fileEven);

    return 0;
}