#include <stdio.h>
#include <math.h>

int divisors(int number) {
    int i, count = 0, st = sqrt(number);

    for (i = 1; i <= st; i++) {
        if (number % i == 0) {
            count += 2;
        }
    }

    if (st * st == number) {
        count--;
    }
    return count;
}

int main() {
    printf("%d\n", divisors(7));
    return 0;
}
