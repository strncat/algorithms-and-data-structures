//
// Karatsuba Integer Multiplication
// not a real implementation, this is just to see how it works recursively
//

#include <stdio.h>
#include <math.h>

int digits(long n) { // there is a better way though, log(n) + 1? 
    int d = 0;
    while (n) {
        n = n/10;
        d++;
    }
    return d;
}

long karatsuba(long x, long y) {
    if (x == 0 || y == 0) {
        return 0;
    }

    // cheating?
    int n = digits(x);
    int m = digits(y);

    if (n <= 1 && m <= 1) {
        return x * y;
    }
    
    // extract a, b, c, d
    long p = (long) pow(10, n/2);
    long q = (long) pow(10, m/2);
    
    long a = x / p;
    long b = x % p;
    long c = y / q;
    long d = y % q;
    
    long ac = karatsuba(a, c);
    long bd = karatsuba(b, d);
    long ab_cd = karatsuba(a + b, c + d);

    // kind of cheating when multipling instead of shifting
    return (ac * p * q) + bd + (ab_cd - bd - ac) * (p < q ? p : q);
}

int main() {
    printf("%ld\n", karatsuba(3250, 48120)); // 156390000
    printf("%ld\n", karatsuba(48120, 3250)); // 156390000
    printf("%ld\n", karatsuba(481290, 993250)); // 478040212500
    printf("%ld\n", karatsuba(7, 888)); // 6216
    return 0;
}
