//
//
//  calculate the gcd and the lcm
//
//
//

#include <iostream>

int gcd(int a, int b) {
    while (a > 0 and b > 0) {
        if (a >= b) {
            a = a % b;
        } else {
            b = b % a;
        }
    }
    return a > b ? a : b;
}

int gcd_recursive(int a, int b) {
    if (b == 0) { return a; }
    return gcd_recursive(b, a % b);
}

int lcm(int a, int b) {
    return b * a / gcd(a, b);
}

int main() {
    printf("%d\n", gcd(38, 76));
    printf("%d\n", gcd_recursive(38, 76));
    printf("%d\n", gcd(30, 345));
    printf("%d\n", gcd_recursive(30, 345));
    printf("%d\n", gcd(22, 44));
    printf("%d\n", gcd_recursive(22, 44));

    return 0;
}


