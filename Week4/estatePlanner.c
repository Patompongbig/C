#include <stdio.h>
#include <math.h>

//O(log(n))

int estate(int m, int n);

int main() {
    int m, n, ans;
    scanf("%d %d", &m, &n);
    ans = estate(m, n);
    printf("%d", ans);
    return 0;
}

int estate(int m, int n){
    int i;

    if (m == 1){
        return n;
    }
    if (n == 1){
        return m;
    }
    if (m == 0){
        return 0;
    }
    if (n == 0){
        return 0;
    }
    for (i = 1; ; i++){
        if (pow(2, i) > m || pow(2, i) > n){
            break;
        }
    }
    i -= 1;
    return 1 + estate(m - pow(2, i), n) + estate(pow(2, i), n - pow(2, i));
}