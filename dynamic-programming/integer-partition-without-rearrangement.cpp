//
//  Integer Partition without Rearrangement
//  Source: Algorithm Design Manual
//
//  Given n elements and k partitions. If we place the last divider between
//  some index i and i+1, the the cost will be the minimum of (over i):
//  the maximum of
//  (1) The cost of the maximum partition to the left of i: m[i,k-1]
//  (2) The sum of elements i+1 to n
//
//
//  Source: Algorithms Design Manual
//  Created by FB on 3/24/17
//

#include <iostream>

#define	MAXN	45
#define MAXK	10

void print_books(int s[], int start, int end) {
    printf("\{");
    for (int i = start; i <= end; i++) {
        printf(" %d ",s[i]);
    }
    printf("}\n");
}

void print_matrix(int m[MAXN+1][MAXK+1], int n, int k) {
    printf("\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            printf(" %d ", m[i][j]);
        }
        printf("\n");
    }
}

void reconstruct_partition(int *s,int d[MAXN+1][MAXK+1], int n, int k) {
    if (k == 1) {
        print_books(s, 1, n);
    } else {
        reconstruct_partition(s, d, d[n][k], k-1);
        print_books(s, d[n][k]+1, n);
    }
}

void partition(int s[], int n, int k) {
    int p[MAXN+1]; // prefix sum {1, 2, 3} = [1, 3, 6]
    int m[MAXN+1][MAXK+1]; // m[n,k] = min(i) { max( m[i,k-1], sum(i+1 to n) }
    int d[MAXN+1][MAXK+1]; // store dividers (parent array) for reconstruction

    p[0] = 0;
    for (int i=1; i<=n; i++) {
        p[i] = p[i-1] + s[i];
    }

    // base cases
    for (int i = 1; i <= n; i++) { // for k = 1, it's just the sum of all elements up to i
        m[i][1] = p[i];
    }
    for (int j = 1; j <= k; j++) { // for n = 1, it's always the first element
        m[1][j] = s[1];
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 2; j <= k; j++) {
            m[i][j] = INT_MAX;
            for (int x = 1; x <= (i-1); x++) {
                int cost = std::max(m[x][j-1], p[i]-p[x]);
                if (m[i][j] > cost) {
                    m[i][j] = cost;
                    d[i][j] = x;
                }
            }
        }
    }
    reconstruct_partition(s, d, n, k);
}

int main() {
    int s[10] = {0,1,2,3,4,5,6,7,8,9}; // starts at index = 1
    partition(s, 9, 3); // n = 9, partitions k = 3
    return 0;
}