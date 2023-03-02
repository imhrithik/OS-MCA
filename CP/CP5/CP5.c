#include <stdio.h>
#include <stdlib.h>

struct student {
    int rollno;
    char name[200];
};

int writef(FILE *file, struct student *s) {
    int out = fprintf(
        file,
        "%d\n%s\n",
        s->rollno, s->name
    );
    fflush(file);
    return out;
}

int readf(FILE *file, struct student *s) {
    if (fscanf(file, "%d", &s->rollno) == EOF) return 0;
    if (fscanf(file, "%s", s->name) == EOF) return 0;
    return 1;
}

int main() {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct student s;
    FILE *file = fopen("Student.txt", "w");
    for (int i = 0; i < n; i++) { 
        printf("Enter the roll no of student %d: ", i);
        scanf("%d", &s.rollno);
        printf("Enter the name of student %d: ", i);
        scanf("%s", s.name);
        writef(file, &s);
    }
    fclose(file);

    file = fopen("Student.txt", "r");
    int i = 0;
    while (readf(file, &s)) {
        printf("Student #%d: %s\n", s.rollno, s.name);
        if(i == 5) break;
        i++;
    }
    fclose(file);

    return 0;
}