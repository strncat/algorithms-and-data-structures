//
// Coin Change Problem
// Practice Problem
// https://www.hackerrank.com/challenges/coin-change
/*
  Total number of solutions =
    For each coin i =
      Number of ways to make change =
         1) We use the coin so we are left now with amount-c[i] + same set of coins
         2) We don't this coin so we are left now with amount + coins except for c[i]
 
 Example amount = 4 and coins = {3, 2, 1}, recursion tree:
                    4
               /         \
        4,{2,1}        3,{3,2,1}  // we either use the coin (amount-coin) or we don't (amount)
        /    \           /    \
     4,{1}  2,{2,1}  3,{2,1} 0,{3,2,1}
    / \       /
 4,{}  3,{1} 2,{1}

*/

#include <stdio.h>
#include <assert.h>
#include <string.h>

// top down
long make_change(int *c, int n, int amount) {
    if (amount == 0) { return 1; } // used coins = exact amount
    if (n <= 0 || amount < 0) { return 0; } // amount is negative or ran out of coins

    // either use the coin or don't
    return make_change(c, n-1, amount) + make_change(c, n, amount - c[n-1]);
}

// bottom up
long long dp[100][100];
long long make_change_bottom_up(int *c, int n, int amount) {
    // base case for amount = 0, there is 1 way to make change no matter what coin it is
    for (int i = 0; i < n; i++) {
        dp[i][0] = 1;
    }
    for (int i = 0; i < n; i++) { // for each coin
        for (int j = 1; j <= amount; j++) { // for each amount

            // dp[n][amount] = dp[n-1][amount] + dp[n][amount-c[n]]

            dp[i][j] = (i == 0) ? 0 : dp[i-1][j];

            dp[i][j] += (j-c[i] < 0) ? 0 : dp[i][j-c[i]];
        }
    }
    return dp[n-1][amount];
}


// bottom up with less memory
long make_change_bottom_up_opt(int *c, int n, int amount) {
    long dp[100];
    memset(dp, 0, sizeof(dp));

    dp[0] = 1; // base case
    for (int i = 0; i < n; i++) { // for each coin
        for (int m = c[i]; m <= amount; m++) { // for each amount, m needs to be >= c[i], start from c[i]
            dp[m] += dp[m - c[i]];
        }
    }
    return dp[amount];
}

void tests() {
    int c2[3] = {1, 2, 3};
    assert(make_change(c2, 3, 4) == 4);
    assert(make_change_bottom_up_opt(c2, 3, 4) == 4);
    assert(make_change_bottom_up(c2, 3, 4) == 4);

    int c1[4] = {1, 5, 10, 20};
    assert(make_change(c1, 4, 10) == 4);
    assert(make_change_bottom_up_opt(c1, 4, 10) == 4);
    assert(make_change_bottom_up(c1, 4, 10) == 4);
}

int main() {
    tests();
    int amount, m, c[51];
    scanf("%d %d", &amount, &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &c[i]);
    }
    printf("%ld\n", make_change_bottom_up_opt(c, m, amount));
}
