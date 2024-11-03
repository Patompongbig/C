#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//O(sqrt(n))

void sort(int *a, int *b);

int main() {
    int m, v, i, j, count, *snack, k;
    scanf("%d", &m);

    snack = (int *)malloc(sizeof(int) * m);
    for (i = 0; i < m; i++){
        scanf("%d", snack[i]);
    }
    for (i = 0; i < m; i++){
        for (j = i+1; j < m; j++){
            sort(&snack[i], &snack[j]);
        }
    }

    scanf("%d", &v);

    for (i = 0; i < m; i++){
        if (v > snack[i]){
            k = v/snack[i];
            v -= snack[i] * k;
            count += 1;
        }
    }

    printf("%d", count);
    
    free(snack);
    return 0;
}

void sort(int *a, int *b){
    int tmp = *a;
    if(*a > *b){
        *a = *b;
        *b = tmp;
    }
}