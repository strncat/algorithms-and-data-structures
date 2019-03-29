//
//
//  Diophantine Equations
//  Given three numbers a, b, and c, the algorithm should return some x and y such that
//  ax + by = c
//
//
//

/*
 Theorem:
 Given integers a and b (at least a or b != 0) the Diophantine equation
 ax + by = c
 has a solution where x and y are integers if and only if
 gcd(a,b)|c

 Theorem:
 let gcd(a,b) = d, a = dp, b = dq.
 if (x0,y0) is a solution of the Diophantine equation ax + by = c: ax0 + by0 = c
 then all the solutions have the form:
 a(x0 + tq) + b(y0 - tp) = c
 where t is an arbitrary integer.
 */

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
    if (a < b) {
        return extended_gcd(b, a);
    }
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

// ax + by = c
std::pair<int,int> Diophantine(int a, int b, int c) {
    //assert(c % gcd(a,b));
    tuple t(0,0,0);
    if (b > a) {
        t = extended_gcd(b, a);
        // swap x and y
        int temp = t.x;
        t.x = t.y;
        t.y = temp;
    } else {
        t = extended_gcd(a, b);
    }
    int f = c/t.d;
    int x = f * t.x;
    int y = f * t.y;
    return std::pair<int,int>(x,y);
}

int main() {

    std::pair<int,int> t1 = Diophantine(3, 6, 18);
    assert(t1.first == 6 && t1.second == 0);

    return 0;
}
