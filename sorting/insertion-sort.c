//
// Insertion Sort, Reference: Algorithms Design Manual
//

#include <stdio.h>

void print(int *a, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insertion_sort(int *a, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (a[j] < a[j - 1]) {
                swap(&a[j - 1], &a[j]);
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    int a[10] = {10,9,8,7,6,5,4,3,2,1};
    print(a, 10);
    insertion_sort(a, 10);
    print(a, 10);
    return 0;
}
