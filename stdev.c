#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void findSD(double *sigma, int *num, int *n){
    int i;
    float average;
    for (i = 0; i < *n; i++){
        average += num[i];
    }
    average /= *n;
    for (i = 0;i < *n; i++){
        *sigma += pow(num[i] - average, 2);
    }
    *sigma = sqrt(*sigma / *n);
}

int main()
{   
    int n, i;
    double sigma;
    int *nums;

    scanf("%d", &n);

    nums = (int *)malloc(sizeof(int) *n);

    for (i = 0; i < n; i++)
        scanf("%d", nums + i);

    findSD(&sigma, nums, &n);

    printf("%.2f", sigma); 
    free(nums);  
    return 0;
}