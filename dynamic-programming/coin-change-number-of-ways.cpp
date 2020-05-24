//
// Coin Change Problem
// Practice Problem
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=2078

/*
  Total number of solutions =
    For each coin i =
      Number of ways to make change =
         1) We use the coin so we are left now with amount-c[i] + same set of coins
         2) We don't this coin so we are left now with amount + coins except for c[i]

 Example amount = 4 and coins = {3, 2, 1}, recursion tree:
                4 {3,2,1}
               /         \
        4,{2,1}        3,{3,2,1}  // we either use the coin (amount-coin) or we don't (amount)
        /    \           /    \
     4,{1}  2,{2,1}  3,{2,1} 0,{3,2,1}
    / \       /
 4,{}  3,{1} 2,{1}

*/

#include <iostream>
#include <vector>

#define MAX_AMOUNT 1000

// top down
long make_change_recursive(std::vector<int>& coins, int n, int amount) {
    if (amount == 0) { // used coins = exact amount
        return 1;
    }

    if (amount < 0) { // not the right combination of coins
        return 0;
    }

    if (n <= 0) { // ran out of coins
        return 0;
    }

    // either use the coin or don't
    return make_change_recursive(coins, n-1, amount) + // don't use this coin
    make_change_recursive(coins, n, amount - coins[n-1]); // use the coin
}

// top down
long make_change_recursive_alt(std::vector<int>& coins, int index, int amount) {
    if (amount == 0) { // used coins = exact amount
        return 1;
    }

    if (amount < 0) { // not the right combination of coins
        return 0;
    }

    int total = 0;
    for (int i = index; i >= 0; i--) {
        // recurse again but with the largest coin = coins[i]
        // this way we don't count duplicates
        total += make_change_recursive_alt(coins, i, amount - coins[i]);
    }

    return total;
}

void make_change_2d(std::vector<int>& coins, std::vector<std::vector<int>>& dp) {
    // base case for amount = 0, there is 1 way to make change
    for (int i = 0; i <= coins.size(); i++) {
        dp[i][0] = 1;
    }
    // otherwise the total number of ways to make change is zero for any amount > 0 with zero coins
    for (int amount = 1; amount <= MAX_AMOUNT; amount++) {
        dp[0][amount] = 0;
    }

    for (int i = 1; i <= coins.size(); i++) { // for each coin
        for (int amount = 1; amount <= MAX_AMOUNT; amount++) { // for each amount
            // dp[n][amount] = dp[n-1][amount] + dp[n][amount-c[n]]
            dp[i][amount] = dp[i-1][amount];

            if (amount >= coins[i-1]) {
                dp[i][amount] += dp[i][amount-coins[i-1]];
            }
        }
    }
}

// bottom up with less memory
void make_change_1d(std::vector<int>& coins, std::vector<int>& dp) {
    dp[0] = 1; // base case
    for (int i = 0; i < coins.size(); i++) { // for each coin
        for (int amount = coins[i]; amount <= MAX_AMOUNT; amount++) { // for each amount, m needs to be >= c[i], start from c[i]
            dp[amount] += dp[amount - coins[i]];
        }
    }
}

void example1() {
    std::vector<int> coins;
    coins.push_back(1);
    coins.push_back(2);
    coins.push_back(3);

    // (1) recursive way (slow)
    assert(make_change_recursive(coins, 3, 4) == 4);
    assert(make_change_recursive_alt(coins, 2, 4) == 4);

    // (2) 2d dynamic programming table
    std::vector<std::vector<int>> dp2(coins.size()+1, std::vector<int>(MAX_AMOUNT+1, 0));
    make_change_2d(coins, dp2);
    assert(dp2[coins.size()][4] == 4);

    // (3) 1d dynamic programming array
    std::vector<int> dp(MAX_AMOUNT+1, 0);
    make_change_1d(coins, dp);
    assert(dp[4] == 4);
}

void example2() {
    std::vector<int> coins;
    coins.push_back(1);
    coins.push_back(5);
    coins.push_back(10);
    coins.push_back(20);

    // (1) recursive way (slow)
    assert(make_change_recursive(coins, 4, 10) == 4);
    assert(make_change_recursive_alt(coins, 3, 10) == 4);

    // (2) 2d dynamic programming table
    std::vector<std::vector<int>> dp2(coins.size()+1, std::vector<int>(MAX_AMOUNT+1, 0));
    make_change_2d(coins, dp2);
    assert(dp2[coins.size()][10] == 4);

    // (3) 1d dynamic programming array
    std::vector<int> dp(MAX_AMOUNT+1, 0);
    make_change_1d(coins, dp);
    assert(dp[10] == 4);
}

int main() {
    example1();
    example2();
}
