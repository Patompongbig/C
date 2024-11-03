#include <stdio.h>

int main()
{   
    int i, j, k, count, pascal;
    scanf("%i", &count);
    for (i = 1; i <= count; i++){
        for (k = count-i; k > 0; k--){
            printf("  ");
        }
        pascal = 1;
        for (j = 1; j <= i; j++){
            printf(" %i  ", pascal);
            pascal = pascal * (i-j)/j;
        }
        printf("\n");
    }
    return 0;
}