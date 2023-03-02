#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file/directory> <permission>\n", argv[0]);
        exit(1);
    }

    char *file = argv[1];
    char *permission = argv[2];
    int mode = strtol(permission, 0, 8);

    if (chmod(file, mode) == -1) {
        perror("chmod");
        exit(1);
    }

    printf("Access rights of %s changed to %s\n", file, permission);
    return 0;
}