#include <stdio.h>
#include <stdlib.h>

void print(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void merge(int a[], int first, int last, int mid) {
    int b[mid - first + 1];
    int c[last - mid];
    int i, j;

    for (i = 0; i < mid - first + 1; i++) {
        b[i] = a[i + first];
    }

    for (j = 0; j < last - mid; j++) {
        c[j] = a[j + mid + 1];
    }
    int k = 0, m = 0, index = first;
    while (k < i && m < j) {
        if (b[k] < c[m]) {
            a[index++] = b[k++];
        } else {
            a[index++] = c[m++];
        }
    }
    while (k < i) { a[index++] = b[k++]; }
    while (m < j) { a[index++] = c[m++]; }
}

void merge_sort(int a[], int begin, int end) {
    if (end - begin > 0) {
        int mid = (end + begin) / 2;
        merge_sort(a, begin, mid);
        merge_sort(a, mid + 1, end);
        merge(a, begin, end, mid);
    }
}

int main() {
    int a[6] = {6, 7, 4, 3, 2, 1};
    print(a, 6);
    merge_sort(a, 0, 5);
    print(a, 6);
    return 0;
}
