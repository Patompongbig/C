#include <stdio.h>
#include <math.h>

//O(sqrt(n))
int prime(long n){
    int i;
    for (i = 2; i <= sqrt(n); i++){
        if (i % n == 0){
            return 0;
        }
    }
    return 1;
}

int main()
{
    long num;
    scanf("%ld", &num);

    if (prime(num)) {
        printf("0");
    } else {
        printf("1");
    }
    return 0;
}