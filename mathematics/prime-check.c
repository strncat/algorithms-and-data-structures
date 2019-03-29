//
//  isPrime
//

#include <stdio.h>
#include <math.h>

int isPrime(int n) {
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    int m = sqrt(n);
    for (int i = 3; i <= m; i += 2) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    printf("%d\n", isPrime(34547));
    printf("%d\n", isPrime(34549));
    return 0;
}
