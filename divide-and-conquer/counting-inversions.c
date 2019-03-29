#include <stdio.h>
#include <stdlib.h>

void print(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int merge(int a[], int first, int last, int mid) {
    int *b = malloc((mid - first + 1) * sizeof(int));
    int *c = malloc((last - mid) * sizeof(int));
    int total = 0;

    int i, j;
    for (i = 0; first + i <= mid; i++) {
        b[i] = a[first + i];
    }
    for (j = 0; mid + 1 + j <= last; j++) {
        c[j] = a[mid + 1 + j];
    }

    int k = 0, m = 0, index = first;
    while (k < i && m < j) {
        if (b[k] < c[m]) {
            a[index++] = b[k++];
        } else {
            a[index++] = c[m++];
            total += (i - k);
        }
    }
    while (k < i) { a[index++] = b[k++]; }
    while (m < j) { a[index++] = c[m++]; }
    free(b); free(c);
    return total;
}

int merge_sort(int a[], int begin, int end) {
    int total = 0;
    if (end - begin > 0) {
        int mid = (end + begin) / 2;
        total = merge_sort(a, begin, mid);
        total += merge_sort(a, mid + 1, end);
        total += merge(a, begin, end, mid);
    }
    return total;
}

int main() {
    int a[6] = {6, 7, 4, 3, 2, 1};
    print(a, 6);
    printf("total inversions = %d\n", merge_sort(a, 0, 5));
    print(a, 6);
    return 0;
}
