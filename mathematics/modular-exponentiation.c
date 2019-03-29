#include <stdio.h>

/* Compute a^e (mod m) = (a % m) * (a % m) * ..... * (a % m) (mod m)
 
 (1) method 1: naive implementation O(e)
 (2) method 2: using divide and conquer
 (3) method 3: using the binary represtation http://en.wikipedia.org/wiki/Modular_exponentiation
 */

// method (1) O(e)
int mod_linear(int b, int e, int m) {
    int c = 1;
    while (e--) {
        c = (b * c) % m;
    }
    return c;
}

// method (2) O(log(e))
/* b = 7 e = 13 m = 11

 (1)  e=13 e/2 = 6
      result = 4
      e is odd
      temp = 4*4 (mod 11) = 5
      temp = temp * 7 (mod 11) = 2

 (2)  e=6 e/2 = 3
      result = 2
      e is even
      return 2*2 (mod 11) = 4


 (3)  e=3 3/2 = 1
      result = 7
      e is odd
      temp = 7*7 (mod 11) = 5
      temp = temp*7 (mod 11) = 2

 (4)  e/2 = 1 return 7%11=7
*/
int mod_binary(int a, int e, int m) {
    if (e == 1) {
        return a % m;
    } else if (e == 0) {
        return 1;
    } else {
        int result = mod_binary(a, e/2, m);
        if (e%2 == 1) { // odd power
            int temp = (result * result) % m;
            temp *= (a % m);
            temp %= m;
            return temp;
        } else { // even power
            return (result * result) % m;
        }
    }
}

// method (3) O(lg(e))
int mod_fast(int b, int e, int m) {
    b = b % m;
    int result = 1;
    
    while (e) {
        if (e % 2 == 1) {
            result = (result * b) % m;
        }
        b = (b * b) % m;
        e >>= 1;
    }
    return result;
}

int main() {
    int b = 4;
    int e = 13; /* in binary = 1101 */
    int m = 497;

    // method 1
    printf("%d\n", mod_linear(b, e, m));

    // method 2
    printf("%d\n", mod_binary(b, e, m));

    // method 3
    printf("%d\n", mod_fast(b, e, m));
    return 0;
}
