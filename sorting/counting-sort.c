//
// Counting Sort: O(n), Source: CLRS
//
// "An important property of counting sort is that it is stable:
// numbers with the same value appear in the output array in
// the same order as they do in the input array"

#include <stdio.h>
#include <stdlib.h>

void print(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void counting_sort(int *a, int n, int k) { // O(n) space and time
    // all elements are in the range of 0 to k
    int c[k+1] = {0};
    int b[n];

    // count elements, c[i] contains the number of elements = i
    // c = {1, 1, 2, 1}
    for (int i = 0; i < n; i++) {
        c[a[i]]++;
    }

    // cumulative counts, c[i] contains the number of elements <= i
    // c = {1, 2, 4, 5}
    for (int i = 1; i <= k; i++)  {
        c[i] += c[i - 1];
    }

    // the value c[a[i]-1] is the correct position of the element a[i] in b
    for (int i = n - 1; i >= 0; i--) {
        b[c[a[i]] - 1] = a[i];
        c[a[i]]--; // because we may have repeated elements
    }

    for (int i = 0; i < n; i++) {
        a[i] = b[i];
    }
}

int main() {
    // Example
    // A: 4 3 2 3 1
    // B: 1 2 3 3 4
    int a[5] = {4, 3, 2, 3, 1};
    print(a, 5);
    counting_sort(a, 5, 4);
    print(a, 5);
    return 0;
}
