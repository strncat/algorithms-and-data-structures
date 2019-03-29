//
// Heap Sort
//

#include <stdio.h>
#include <stdlib.h>

#define PQ_SIZE 100000

typedef struct {
    int buffer[PQ_SIZE+1];
    int n;
} heap;

int left_child(int parent) {
    return (2 * parent);
}

int right_child(int parent) {
    return (2 * parent) + 1;
}

int get_parent(int child) {
    if (child == 1)
        return -1;
    return child/2;
}

void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

void bubble_down(heap *q, int parent) {
    int child = left_child(parent);
    int min = parent;

    for (int i = 0; i <= 1; i++) {
        if ((child + i) <= q->n) {
            if (q->buffer[min] < q->buffer[child + i]) {
                min = child + i;
            }
        }
    }
    if (min != parent) {
        swap(&q->buffer[min], &q->buffer[parent]);
        bubble_down(q, min);
    }
}

int extract_max(heap *q) {
    int maximum = q->buffer[1];
    q->buffer[1] = q->buffer[q->n];
    (q->n)--;
    bubble_down(q, 1);
    return maximum;
}

void print(int *a, int n) {
    for(int i = 0; i < 6; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void make_heap(heap *q, int *s, int n) {
    q->n = n;
    for (int i = 0; i < n; i++) {
        q->buffer[i+1] = s[i];
    }
    for (int i = q->n; i >= 1; i--) {
        bubble_down(q, i);
    }
}

void heap_sort(int *s, int n) { /* O(nlogn) */
    heap q;
    make_heap(&q, s, n);
    for (int i = 0; i < n; i++) {
        s[i] = extract_max(&q);
    }
}

int main() {
    int s[6] = {5, -2, 10, 6, 20, -10};
    print(s, 6);
    heap_sort(s, 6);
    print(s, 6);
    return 0;
}
