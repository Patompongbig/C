#include <stdio.h>
#include <math.h>

typedef struct student {
    char name[20];
    int grade;
} student_t;

void inputStudent(student_t students[], int n) {
    int i;
    for (i = 0; i < n; i++){
        scanf("%s %d", students[i].name, &students[i].grade);
    }
}

void showStudentGrade(student_t students[], int n) {
    int i;
    double mean = 0, sd = 0;
    
    for (int i = 0; i < n; i++){
        mean += students[i].grade;
    }
    mean /= n;
    
    for (int i = 0; i < n; i++){
        sd += pow(students[i].grade - mean, 2);
    }
    sd = sqrt(sd/n);
    
    for (int i = 0; i < n; i++){
        if (students[i].grade >= mean + (1.5 * sd)){
            printf("%s A\n", students[i].name);
        }
        else if (students[i].grade >= mean + sd){
            printf("%s B\n", students[i].name);
        }
        else if (students[i].grade >= mean - sd){
            printf("%s C\n", students[i].name);
        }
        else if (students[i].grade >= mean - (1.5 * sd)){
            printf("%s D\n", students[i].name);
        }
        else if (students[i].grade < mean - (1.5 * sd)){
            printf("%s F\n", students[i].name);
        }
    }    
}

int main(void) {
    student_t students[1000];
    int n;

    scanf("%d", &n);
    inputStudent(students, n);
    showStudentGrade(students, n);
    return 0;
}