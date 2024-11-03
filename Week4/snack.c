#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//O(n)

int main() {
    int m, v, i, j, count, k;
    scanf("%d", &m);

    int snack[100001] = {0};
    for (i = 0; i < m; i++){
        scanf("%d", &v);
        snack[v] = v;
    }

    scanf("%d", &v);

    for (i = 100000; i > 0; i--){
        if (snack[i]){
            k = v/snack[i];
            v -= snack[i] * k;
            count += 1 * k;
        }
    }

    printf("%d", count);

    return 0;
}