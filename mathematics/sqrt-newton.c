#include <stdio.h>
#include <stdlib.h>

/* sqrt using newton */

#define epislon 00000000001

double sqrt_newton(double y) {
    if (y < 0) { return -1.0; }

    double x = y;
    while (abs(y - x*x) > epislon) {
        x = x - (x*x - y) / (2*x);
    }
    return x;
}

int main() {
    printf("sqrt(21) = %f\n", sqrt_newton(21));
    printf("sqrt(16) = %f\n", sqrt_newton(16));
    printf("sqrt(144) = %f\n", sqrt_newton(144));
    return 0;
}
