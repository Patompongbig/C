#include <stdio.h>

void calender(int year, int month);

int main()
{
    int year, month;
    printf("Enter year: ");
    scanf("%d", &year);
    printf("Enter month: ");
    scanf("%d", &month);
    printf("====================\n");
    calender(year, month);

    return 0;
}

void calender(int year, int m){
    const char *month[] = {"January", "February", "March", 
    "April", "May", "June", 
    "July", "August", "Setember", 
    "October", "November", "December"};
    int day[] = {31, 28, 31, 
    30, 31, 30, 
    31, 31, 30, 
    31, 30, 31};
    int gap;
    int dayto = 0;
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
        day[1] = 29;
    }
    for (gap = 1990; gap < year; gap++){
        if ((gap % 4 == 0 && gap % 100 != 0) || (gap % 400 == 0)){
            dayto += 366;
        }
        else{
            dayto += 365;
        }
    }
    for (gap = 0; gap < m-1; gap++){
            dayto += day[gap];
    }
    int i;
    dayto = (dayto % 7) + 1;
    printf("%s %i\n", month[m - 1], year);
    printf("Sun Mon Tue Wed Thu Fri Sat\n");
    if (dayto < 7){
        for (i = 0; i < dayto; i++){
            printf("    ");
        }
    }
    for (i = 1; i <= day[m-1]; i++){
        if (dayto == 7){
            if (i == 1){
                dayto = 0;
            }
            else {
                printf("\n");
                dayto = 0;
            }
        }
        if (i < 10){
            printf("  %i ", i);
            dayto += 1;
        }
        else{
            printf(" %i ", i);
            dayto += 1;
        }
    }
    printf("\n");
}