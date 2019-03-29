//
//  Longest Increasing Subsequence O(n^2)
//  2014
//
/*
 7 2 8 1 3 4 10 6 9 5
 // make a new array c where c[i] is the maximum increasing subsequence ending at a[i]
 // the c array for the above array would look like
 // 1 1 2 1 2 3 4 4 5 4
 */

#include <iostream>

void print(int *a, int *p, int index) {
    if (index == -1) {
        return;
    }
    print(a, p, p[index]);
    printf("%d ", a[index]);
}

void longest_increasing_subsequence(int *a, int n) { /* O(n^2) */
    int c[n], p[n], max = 0, maxIndex = 0;

    // maximum subsequence ending at a[i] is initialy 1
    for (int i = 0; i < n; i++) {
        c[i] = 1;
        p[i] = -1; // parent array
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[i] > a[j] && c[i] < c[j] + 1) { // I can extend the subsequence
                c[i] = c[j] + 1;
                p[i] = j;
            }
        }
        if (c[i] > max) { // maximum subsequence so far
            max = c[i];
            maxIndex = i;
        }
    }
    print(a, p, maxIndex);
}

int main() {
    int a[10] = {7, 2, 8, 1, 3, 4, 10, 6, 9, 5};
    longest_increasing_subsequence(a, 10);
    return 0;
}
