#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isPrime(int n) {
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i <= (int)sqrt((double)n); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        printf("Usage: ./a.out min max\n");
        return 1;
    }
    int min = atoi(argv[1]);
    int max = atoi(argv[2]);

    for (int i = min; i <= max; i++) {
        if (isPrime(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
    return 0;
}
