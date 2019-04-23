//
//  main.cpp
//  rmq
//
//  Created by FB on 4/3/19.
//  Copyright © 2019 FB. All rights reserved.
//



#include <iostream>
#include <limits.h>
#include <math.h>

#define MAX 19
#define LOGMAX 5

// APPROACH 2 naive implementation
void preprocess_naive(int *a, int n, int naive[MAX][MAX]) { // O(n^3)
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // for range i..j
            int min = INT_MAX;
            for (int k = i; k <= j; k++) {
                if (min > a[k]) {
                    min = a[k];
                }
            }
            naive[i][j] = min;
        }
    }
}

// APPROACH 3 dynamic programming
void preprocess_dp(int *a, int n, int dp[MAX][MAX]) { // O(n^2)
    // given the minimum to range dp[i,j-1], the minimum to range [i,j+1] = min(dp[i,j-1],a[j])
    for (int i = 0; i < n; i++) {
        dp[i][i] = a[i];
    }
    for (int i = 1; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            // for range i..j
            dp[i][j] = std::min(dp[i][j-1],a[j]);
        }
    }
}

// APPROACH 4 blocks
void preprocess_block(int *a, int n, int b, int *block) { // O(n)
    int j = -1;
    for (int i = 0; i < n; i++) {
        block[i] = INT_MAX;
    }
    for (int i = 0; i < n; i++) {
        if (i % b == 0) {
            j++;
        }
        if (a[i] < block[j]) {
            block[j] = a[i];
        }
    }
}

void test_naive(int *a, int n) {
    int naive[MAX][MAX];
    preprocess_naive(a, n, naive);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            printf("\t");
        }
        for (int j = i; j < n; j++) {
            printf("%d\t", naive[i][j]);
        }
        printf("\n");
    }
}

void test_dp(int *a, int n) {
    int dp[MAX][MAX];
    preprocess_dp(a, n, dp);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            printf("\t");
        }
        for (int j = i; j < n; j++) {
            printf("%d\t", dp[i][j]);
        }
        printf("\n");
    }
}

void test_block(int *a, int n) {
    int block[MAX];
    int b = 4; // sqrt(16) = 4;
    preprocess_block(a, n, b, block);

    // query time
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            printf("\t");
        }
        for (int j = i; j < n; j++) {
            // given indices i and j
            int block_i = i/b;
            int block_j = j/b;
            int min = INT_MAX;
            for (int k = block_i + 1; k < block_j; k++) {
                if (min > block[k]) {
                    min = block[k];
                }
            }
            int k = std::max(i, block_i*b);
            int m = std::min(block_i*b+b, j);
            for (; k <= m; k++) {
                if (min > a[k]) {
                    min = a[k];
                }
            }
            k = std::max(i, block_j*b);
            m = std::min(block_j*b+b, j);
            for (; k <= m; k++) {
                if (min > a[k]) {
                    min = a[k];
                }
            }
            printf("%d\t", min);
        }
        printf("\n");
    }
}

// APPROACH 5 sparse
void preprocess_sparse(int *a, int n, int M[MAX][LOGMAX]) { // O(nlog(n))
    // 2^0
    for (int i = 0; i < n; i++) {
        M[i][0] = a[i];
    }

    int lg = log2(n);

    // for each power of 2
    for (int j = 1; j <= lg; j++) {
        // fill each row
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            M[i][j] = std::min(M[i][j-1], M[i+(1<<(j-1))][j-1]);
        }
    }
}

void test_sparse(int *a, int n) {
    int M[MAX][LOGMAX];
    preprocess_sparse(a, n, M);

    // query time
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            printf("\t");
        }
        for (int j = i; j < n; j++) {
            // given indices i and j
            int k = log2(j-i+1);
            printf("%d\t", std::min(M[i][k], M[j-(1<<k)+1][k]));
        }
        printf("\n");
    }
}

int main() {
    int a[MAX] = {17, 13, 11, 31, 13, 23, 47, 51, 19, 43, 37, 5, 7, 31, 71, 29, 4, 18, 4};
    //int a[MAX] = {31,41,59,26,53,58,97,93};
    //test_naive(a, MAX);
    //test_dp(a, MAX);
    test_block(a, MAX);
    test_sparse(a, MAX);
    return 0;
}
