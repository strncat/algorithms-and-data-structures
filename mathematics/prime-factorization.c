#include <stdio.h>

void prime_factorization(long int n) {
    while ((n % 2) == 0) {
        printf("2 ");
        n /= 2;
    }
    for (long int i = 3; i * i <= n; i+=2) {
        while (n % i == 0) {
            printf("%ld ", i);
            n = n / i;
        }
    }
    if (n > 2) {
        printf("%ld ", n);
    }
    printf("\n");
}

int main() {
    prime_factorization(600851475143);
    return 0;
}
