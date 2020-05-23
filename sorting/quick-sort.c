//
//
// Quick Sort, Source: Algorithms Design Manual
//
//

#include <stdio.h>

void print(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

int partition(int *a, int first, int last, int n) {
    // (1) We choose a random pivot
    srand(time(NULL));
    int random_pivot = rand() % (last+1-first) + first;
    // otherwise could choose just the first element

    // (2) We put the pivot element at the end of the array
    swap(&a[random_pivot], &a[last]);

    // (3) our pivot pointer is now pointing at the last element of the array
    int pivot = last;

    int index = first;
    for (int i = first; i < last; i++) {                                                      
        if (a[i] < a[pivot]) {
            swap(&a[i], &a[index]);
            index++;
        }
    }
    swap(&a[pivot], &a[index]);
    return index;
}

void quicksort(int *a, int first, int last, int n) {
    int p; /* partition index */
    if (first < last) {
        p = partition(a, first, last, n);
        quicksort(a, first, p - 1, n);
        quicksort(a, p + 1, last, n);
    }
}

int main() {
    int n = 9;
    int a[9] = {9, 6, 3, 2, 5, 1, 4, 8, 7};
    print(a, n);
    quicksort(a, 0, n - 1, n);
    print(a, n);
    return 0;
}
