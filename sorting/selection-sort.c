//
// Selection Sort O(N^2)
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

void selection_sort(int *a, int n) {
    for (int i = 0; i < n; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) { // find the minimum element in the array
            if (a[j] < a[min]) {
                min = j;
            }
        }
        swap(&a[i], &a[min]); // swap the minimum element with the current element
    }
}

int main(int argc, const char * argv[]) {
    int a[10] = {10,9,8,7,6,5,4,3,2,1};
    print(a, 10);
    selection_sort(a, 10);
    print(a, 10);
    return 0;
}
