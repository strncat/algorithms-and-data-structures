#include <stdio.h>
#include <limits.h>

/* The Coin Change Problem
 The minimum number of coins you need to make change for N cents
 Assume that your coins are {20, 10, 5, 1} d1 = 20, d2= 10, d3= 5, d4 = 1
 
 If you knew that one of the coins used in the optimal solution is "d"
 then the minimum number of coins is c[N] = 1 + c[N - d]
 since we don't know "d", we try every possible d => 20, 10, 5 and 1
 
To find the minimum number of coins needed for N cents is
 
 INF or INT_MAX                            if N < 0
 0                                         if N = 0
 1 + min {c[N - di]} over all possible di  if N > 0
 
 To save time, we build up the table until we reach our c[N] and return it
*/

#define N 4
int d[N] = {20, 10, 5, 1};
int c[10] = {0};
int a[10] = {0};

int build_exchange(int note) {
    int i, j, min;
    
    c[0] = 0;
    for (i = 1; i <= note; i++) {
        min = INT_MAX - 1; /* avoid overflow */
        for (j = 0; j < N; j++) { /* for each currency or di */
            if (i - d[j] >= 0 && min > c[i - d[j]]) { /* make sure index exist c[i - d[j]] is not c[-1] */
                min = c[i - d[j]];
            }
        }
        c[i] = min + 1;
    }
    return c[note];
}

int main() {
    printf("%d\n", build_exchange(10));
    return 0;
}
