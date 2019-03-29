//
// Sieve_of_Eratosthenes Ref: Algorithms in C
// (0) Make an array of N integers, set every element a[i] as prime (a[i] = 1) (except for a[0] and a[1])
// (1) Starting with i = 2, unset all multiples of i as they are not primes [0, 0, 1, 1, 0, 1, 0]
// (2) Next iteration we pick the next i that is not yet set and repeat step (1)
//

#include <stdio.h>

void print(int *primes, int n) {
    int count = 0;
    for (int i = 2; i < n; i++) {
        if (primes[i] == 1) {
            printf("%d ", i);
            count++;
        }
    }
    printf("\nnumber of primes = %d\n", count);
}

void sieve(int *primes, int n) { /* Ref: Algorithms in C */
    primes[1] = 0;
    for (int i = 2; i <= n; i++) {
        primes[i] = 1;
    }
    for (int i = 2; i <= n/2; i++) {
        for (int j = 2; j <= n/i; j++) {
            primes[i*j] = 0;
        }
    }
}

void sieve2(int *primes, int n) { /* another implementation */
    for (int i = 0; i < n; i++) {
        primes[i] = 1;
    }
    primes[0] = primes[1] = 0;
    for (int i = 2; i <= n/2; i++) {
        if (primes[i] == 1) {
            for (int j = i*i; j < n; j += i) {
                primes[j] = 0;
            }
        }
    }
}

int main() {
    int n = 10000;
    int primes[n];
    sieve(primes, n);
    sieve2(primes, n);
    print(primes, n);
    return 0;
}
