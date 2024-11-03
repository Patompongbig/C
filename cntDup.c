#include <stdio.h>

void sort(int *a, int *b);

int main()
{
    int store, i, num, j, o_count = 1, n_count = 1, point = 0;
    int subarray[20] = {0};

    scanf("%i", &store);

    int numarray[store];

    for (i = 0; i < store; i++){
        scanf("%i", &num);
        numarray[i] = num;
    }

    for (i = 0; i < store; i++){
        for (j = i+1; j < store; j++){
            sort(&numarray[i], &numarray[j]);
        }
    }

    for (i = 0; i < store - 1; i++){
        if (numarray[i] == numarray[i+1]){
            o_count += 1;
            if (o_count > n_count){
                n_count = o_count;
                subarray[0] = numarray[i];
                point = 1;
            }
            else if (o_count == n_count){
                subarray[point] = numarray[i];
                point += 1;
            }
        }
        else{
            o_count = 1;
        }
    }

    if (n_count == 1){
        for (i = 0; i < store; i++){
            printf("%d", numarray[i]);
        }
    }
    else{
        for (i = 0; i < point; i++){
            printf("%d ", subarray[i]);
        }
    }
    return 0;
}

void sort(int *a, int *b){
    int tmp = *a;
    if(*a > *b){
        *a = *b;
        *b = tmp;
    }
}
