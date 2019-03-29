//
//
//  Source: Programming Challenges Book/Coursera
//  Chapter 7: Find x, y and d in p*x + q*y = d = gcd(p,q)
//  2017/03/05
//
//

#include <iostream>
#include <math.h>
#include <assert.h>

struct tuple {
    int d;
    int x;
    int y;
    tuple(int d, int x, int y) {
        this->x = x;
        this->y = y;
        this->d = d;
    }
};

// find x, y and d in a*x + b*y = d = gcd(a,b)
tuple extended_gcd(int a, int b) {
    if (b > a) { return extended_gcd(b, a); }

    if (b == 0) {
        return tuple(a, 1, 0);
    }

    // d = gcd(a,b) = gcd(b,a%b)
    // d = gcd(b, (a-floor(a/b)*b))
    // d = pb + (a-floor(a/b)*b)q
    // d = pb + aq - floor(a/b)bq
    // d = aq + b(p - q*floor(a/b))

    tuple t = extended_gcd(b, a%b);
    int x = t.y;
    int y = t.x - t.y*floor(a/b);

    return tuple(t.d, x, y);
}

int main() {
    tuple t1 = extended_gcd(10,6);
    assert(t1.d == 2 && t1.x == -1 && t1.y == 2);

    tuple t2 = extended_gcd(7,5);
    assert(t2.d == 1 && t2.x == -2 && t2.y == 3);

    tuple t3 = extended_gcd(391,299);
    assert(t3.d == 23 && t3.x == -3 && t3.y == 4);

    tuple t4 = extended_gcd(239,201);
    assert(t4.d == 1 && t4.x == -37 && t4.y == 44);
    return 0;
}
