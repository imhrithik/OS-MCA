#include <stdlib.h>
#include <stdio.h>

int main() {
    char* arr = (char *) malloc(26 * sizeof(char));
    for (int i = 0; i < 26; i++)
        arr[i] = 'a' + i;
    for (int i = 0; i < 24; i += 2)
        printf("%c, ", arr[i]);
    printf("%c\n", arr[24]);
    free(arr);
    return 0;
}