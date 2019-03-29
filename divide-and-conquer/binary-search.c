#include <stdio.h>

void print_array(int *a, int length) {
    for (int i=0; i<length; i++) {
        printf("%d, ",a[i]);
    }
    printf("\n");
}

int binary_search(int *a, int key, int n) {
    int mid = -1, first = 0, last = n - 1;

    while (first <= last) {
        mid = (first + last) / 2;
        if (key > a[mid]) {
            first = mid+1;
        } else if (key < a[mid]) {
            last = mid-1;
        } else if (key == a[mid]) {
            return mid;
        }
    }
    return mid;
}

int binary_search_recursive(int *a, int key, int first, int last) {
    int mid = (first + last) / 2;
    if (first <= last) {
        if (key > a[mid]) {
            return binary_search_recursive(a, key, mid+1, last);
        } else if (key < a[mid]) {
            return binary_search_recursive(a, key, first, mid-1);
        } else if (key == a[mid]) {
            return mid;
        }
    }
    return -1;
}

int main(void) {
    int a[10] = {1,2,3,4,5,6,7,8,9,10};
    print_array(a, 10);
    printf("%d\n", binary_search_recursive(a, 1, 0, 9));
    printf("%d\n", binary_search_recursive(a, 11, 0, 9));
    printf("%d\n", binary_search_recursive(a, 10, 0, 9));
    return 0;
}
