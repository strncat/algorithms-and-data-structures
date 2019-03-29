//
//  main.cpp
//  Binomial Coefficients
//  Dynamic Programming
//  Reference: Algorithm Design Manual page 280
//
//  Created by Fatima B on 10/2/15.
//  Copyright © 2015 nemo. All rights reserved.
//

#include <iostream>

#define MAX 100
long long table[MAX+1][MAX+1];

void init_binomial_coefficients() {
    for (int i = 0; i <= MAX; i++) { // (n 0) = 1
        table[i][0] = 1;
    }
    for (int j = 0; j <= MAX; j++) { // (n n) = 1
        table[j][j] = 1;
    }
    for (int i = 1; i <= MAX; i++) { // n
        for (int j = 1; j < MAX; j++) { // k
            table[i][j] = table[i-1][j] + table[i-1][j-1];
        }
    }
}

long long binomial_coefficient(int n, int k) {
    return table[n][k];
}

void tests() {
    init_binomial_coefficients();
    if (table[7][0] != 1) { printf("(7 0) != %lld\n", table[7][0]); }
    if (table[4][2] != 6) { printf("(4 2) != %lld\n", table[4][2]); }
    if (table[10][5] != 252) { printf("(10 5) != %lld\n", table[10][5]); }
    if (table[4][4] != 1) { printf("(4 4) != %lld\n", table[4][4]); }
    if (table[7][5] != 21) { printf("(7 5) != %lld\n", table[7][5]); }
}

int main() {
    tests();
    return 0;
}
