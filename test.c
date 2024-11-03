#include <stdio.h>
#include <math.h>

//O(sqrt(n))

int prime(long n) {
    if (n <= 3) {
        return 1;
    }
    int i;
    for (i = 2; i <= sqrt(n); i++) { //O(sqrt(n))
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    long num;
    scanf("%ld", &num);

    if (prime(num)) {
        printf("1");
    } 
    else {
        printf("0");
    }

    return 0;
}
