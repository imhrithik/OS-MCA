#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <utime.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

struct Ex {
    int A;
    char B;
};

int writef(FILE *file, struct Ex *e) {
    int out = fprintf(
        file,
        "\nA:%d\nB:%c",
        e->A, e->B
    );
    fflush(file);
    return out;
}

// using fseek to skip read pointer in the file
int readf(FILE *file, struct Ex *e) {
    fseek(file, 3, SEEK_CUR);
    if (fscanf(file, "%d", &e->A) == EOF) return 0;
    fseek(file, 3, SEEK_CUR);
    if (fscanf(file, "%s", &e->B) == EOF) return 0;
    return 1;
}

int print_time(char* filename) {
    struct stat sb;
    if (stat(filename, &sb) == 0) {
        printf("Modification time for %s: %s", filename, ctime(&sb.st_mtime));
        printf("Access time for %s: %s", filename, ctime(&sb.st_atime));
        return 1;
    }
    return 0;
}

int print_file_access(char* filename) {
    struct stat sb;
    if (stat(filename, &sb) != -1) {
        printf("File access mode for file %s: %o\n", filename, sb.st_mode & 0777);
        return 1;
    }
    return 0;
}

int main() {

    // Creating a example file and writing data to it
    char* filename = "example.txt";
    struct Ex s;
    FILE *file = fopen(filename, "w");
    for (int i = 0; i < 5; i++) {
        s.A = i + 1;
        s.B = i + 'A';
        writef(file, &s);
    }
    fclose(file);

    // lseek -> fseek
    printf("\nlseek:\n");
    file = fopen(filename, "r");
    while (readf(file, &s)) {
        printf("A: %d\n", s.A);
        printf("B: %c\n", s.B);
    }
    fclose(file);

    filename = "test.txt";

    // berfore changing umask
    printf("\nno umask:\n");
    remove(filename);
    fclose(fopen(filename, "w"));
    print_file_access(filename);

    // after changing umask
    printf("\numask:\n");
    umask(S_IRUSR | S_IEXEC); 
    remove(filename);
    fclose(fopen(filename, "w"));
    print_file_access(filename);

    // changing the mode of the file
    printf("\nchmode:\n");
    chmod(filename, S_IWUSR | S_IXUSR);
    print_file_access(filename);

    // Access cheking the read, write access
    printf("\naccess:\n");
    if (access(filename, R_OK) == 0) {
        printf("File is readable\n");
    } else {
        printf("File is not readable\n");
    }

    if (access(filename, W_OK) == 0) {
        printf("File is writable\n");
    } else {
        printf("File is not writable\n");
    }

    // Getting the time modifier of a file test.txt
    printf("\nBefore Changing Time modifier: \n");
    print_time(filename);

    struct utimbuf times;
    time_t current_time = time(NULL);
    times.actime = current_time + (24 * 60 * 60);
    times.modtime = current_time - (24 * 60 * 60);

    // Changing the time modifier of the file
    if (utime(filename, &times) == 0) {
        printf("\nAfter Changing Time modifier: \n");
        print_time(filename);
    }

    return 0;
}