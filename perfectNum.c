#include <stdio.h>

int factor(long num);

int main()
{
    long num, i, ans = 1;
    printf("");
    scanf("%ld", &num);
    for (i = 2; i < num; i++){
        if (i % 2 != 0){
            continue;
        }
        if (i == factor(i)){
            ans = i;
        }
    }
    printf("%ld", ans);
    
    return 0;
}

int factor(long num){
    long ans = 0, i;
    for (i = num/2; i >= 1; i--){
        if (num % i == 0){
            ans += i;
        }
        if (ans > num){
            break;
        }
    }
    return ans;
}