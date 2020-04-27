//
//
// max-heap, Reference: CLRS
//
//

#include <iostream>
#include <algorithm>

#define MAX 10

typedef struct priority_queue {
    int A[MAX];
    int length;
    priority_queue() {
        length = 0;
    }

    int left(int i) { return i << 1; }
    int right(int i) { return (i << 1) + 1; }
    int parent(int i) {
        if (i == 1) { return -1; }
        return (i >> 1);
    }

    // in the algorithm design manual, this is called bubble down
    // we let A[i] floats down until the heap obeys the heap property
    void max_heapify(int i) { // O(h) = O(log(n))
        int l = left(i);
        int r = right(i);

        // (1) check if the left child is greater
        int largest = i;
        if (l <= length && A[l] > A[i]) {
            largest = l;
        } else {
            largest = i;
        }

        // (2) check if the right child is greater
        if (r <= length && A[r] > A[largest]) {
            largest = r;
        }

        // if one of the children is greater, swap it
        // with i and then call heapify again on the child
        // we swapped with
        if (largest != i) {
            std::swap(A[i], A[largest]);
            max_heapify(largest);
        }
    }

    void build_max_heap(int *a, int n) { // O(n)!!!
        // for the heap, indexing starts at 1
        for (int i = 0; i < n; i++) {
            A[i+1] = a[i];
        }

        length = n;
        for (int i = n/2; i >= 1; i--) {
            max_heapify(i);
        }
    }

    int extract_max() {
        int maximum = A[1];
        //printf("A[1] = %d\n", A[1]);
        A[1] = A[length];
        (length)--;
        max_heapify(1);
        return maximum;
    }
} priority_queue;

int main() {
    priority_queue q;
    int a[10] = {-2, 5, 2, 7, 1, 11, 3};

    q.build_max_heap(a, 7);

    while (q.length > 0) {
        printf("%d ", q.extract_max());
    }
    printf("\n");
    return 0;
}
