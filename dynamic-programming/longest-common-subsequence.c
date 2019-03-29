#include <stdio.h>

#define N 4
#define M 7

/* Longest Common Subsequence, Reference: Introduction to Algorithms */

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int LCS(int *a, int *b, int c[N+1][M+1], int n, int m) {
    int i, j;
    
    for (i = 0; i < n; i++) {
        c[i][0] = 0;
    }
    for (j = 0; j < m; j++) {
        c[0][j] = 0;
    }
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                c[i][j] = 1 + c[i - 1][j - 1];
            } else {
                c[i][j] = max(c[i - 1][j], c[i][j - 1]);
            }
        }
    }
    return c[n][m];
}

int main() {

    int i, j;
    int a[N] = {1, 2, 3, 4};
    int b[M] = {2, 3, 1, 1, 2, 3, 4};
    int c[N+1][M+1] = {0};
    
    printf("%d\n", LCS(a, b, c, N, M));
    
    /* Print The Matrix */
    for (i = 0; i < N+1; i++) {
        for (j = 0; j < M+1; j++) {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

