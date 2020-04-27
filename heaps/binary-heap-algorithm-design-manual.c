//
// max-heap, Reference: Algorithms Design Manual
//

#include <stdio.h>
#include <stdlib.h>

#define PQ_SIZE 100000

typedef struct {
    int buffer[PQ_SIZE+1];
    int n;
} heap;

void pq_init(heap *q) {
    q->n = 0;
}

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

void bubble_up(heap *q, int child) {
    int parent = get_parent(child);

    if (parent == -1) {
        return;
    } else if (q->buffer[parent] < q->buffer[child]) {
        swap(&q->buffer[child], &q->buffer[parent]);
        bubble_up(q, parent);
    }
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

void insert(heap *q, int x) {
    (q->n)++;
    q->buffer[q->n] = x;
    bubble_up(q, q->n);
}

void pq_print(heap *q) {
    for (int i = 1; i <= q->n; i++) {
        printf("%d ", q->buffer[i]);
    }
    printf("\n");
}

// heapSort related
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

void print(int *a, int n) {
    for(int i = 0; i < 6; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    heap *q = malloc(sizeof(heap));

    insert(q, 5);
    insert(q, -2);
    insert(q, 10);

    while (q->n > 0) {
        printf("%d ", extract_max(q));
    }
    printf("\n");

    insert(q, 6);
    insert(q, 20);
    insert(q, -10);

    while (q->n > 0) {
        printf("%d ", extract_max(q));
    }
    printf("\n");

    // HeapSort Example
    int s[6] = {5, -2, 10, 6, 20, -10};
    print(s, 6);
    heap_sort(s, 6);
    print(s, 6);
    return 0;
}
