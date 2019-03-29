#include <stdio.h>

// find the largest matrix with 1s
// source geeksforgeeks
// 20140810

#define R 6
#define C 5

int min(int a, int b, int c) {
    
    if (a < b && a < c) {
        return a;
    } else if (b < a && b < c) {
        return b;
    } else {
        return c;
    }
}

void largest_subarray_with_ones(int a[R][C]) {
    
    int i, j, S[R][C], max, max_i, max_j;
    
    for (i = 0; i < R; i++) // copy first column
        S[i][0] = a[i][0];
    
    for (j = 0; j < C; j++) // copy first row
        S[0][j] = a[0][j];
    
    // algorithm
    for (i = 1; i < R; i++) {
        for (j = 1; j < C; j++) {
            if (a[i][j] == 1) {
                S[i][j] = min(S[i][j-1], S[i-1][j], S[i-1][j-1]) + 1;
            } else {
                S[i][j] = 0;
            }
        }
    }

    // printing the actual matrix
    max = S[0][0];
    max_i = 0;
    max_j = 0;
    
    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            if (max < S[i][j]) {
                max = S[i][j];
                max_i = i;
                max_j = j;
            }
        }
    }

    for(i = max_i; i > max_i - max; i--) {
        for(j = max_j; j > max_j - max; j--) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}


int main() {

    int a[R][C] =  {0, 1, 1, 0, 1,
                    1, 1, 0, 1, 0,
                    0, 1, 1, 1, 0,
                    1, 1, 1, 1, 0,
                    1, 1, 1, 1, 1,
                    0, 0, 0, 0, 0};
    
    largest_subarray_with_ones(a);
}
