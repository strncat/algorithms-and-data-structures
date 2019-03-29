//
// Radix Sort, Source: CLRS
//
/*
 Radix sort sorts on the least significant digit first. The algorithm then
 sorts the entire deck again on the second-least significant digit and
 recombines the deck in a like manner. The process continues until the
 cards have been sorted on all d digits. Remarkably, at that point the cards
 are fully sorted on the d-digit number. Thus, only d passes through
 the deck are required to sort
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void print(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void counting_sort(int *a, int n, int k) { // O(n) space and time
    int b[n], c[10] = {0}; // 10 digits every time

    for (int i = 0; i < n; i++) {
        c[(a[i]/k) % 10]++;
    }

    for (int i = 1; i < 10; i++)  {
        c[i] += c[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        b[ (c[(a[i]/k) % 10] - 1) ] = a[i];
        c[(a[i]/k) % 10]--; // because we may have repeated elements
    }

    for (int i = 0; i < n; i++) {
        a[i] = b[i];
    }
}

void radix_sort(int *a, int n) { // O(d(n + k))
    int i, e, max = INT_MIN;
    for (i = 0; i < n; i++) { // max element
        if (a[i] > max) {
            max = a[i];
        }
    }
    // we start sorting with the least significant digit
    // we require d passes (d is the number of digits in the largest element)
    for (e = 1; max/e > 0; e *= 10) {
        counting_sort(a, n, e);
    }
}

int main() {
    int a[5] = {170, 801, 35, 9, 66};
    radix_sort(a, 5);
    print(a, 5);
    return 0;
}
