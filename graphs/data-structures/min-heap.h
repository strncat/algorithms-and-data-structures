//
// Reference: Algorithms Design Manual
// 2013
// minheap
//

#include <stdio.h>

#define PQ_SIZE 30000

typedef struct {
    int u;
    long int cost;
} pair;

typedef struct {
    pair q[PQ_SIZE + 1];
    int n;
} priority_queue;

void pq_init(priority_queue *pq) {
    pq->n = 0;
}

int left_child(int parent) {
    return (2 * parent);
}

int right_child(int parent) {
    return (2 * parent) + 1;
}

int pq_parent(int child) {
    if (child == 1) { /* root */
        return -1;
    }
    return (child/2);
}

void swap(pair *p1, pair *p2) {
    pair temp;
    temp.u = p1->u;
    temp.cost = p1->cost;
    p1->u = p2->u;
    p1->cost = p2->cost;
    p2->u = temp.u;
    p2->cost = temp.cost;
}

void bubble_up(priority_queue *p, int child) {
    int parent = pq_parent(child);
    if (parent == -1) { /* root! */
        return;
    } else if (p->q[parent].cost > p->q[child].cost) { /* swap */
        swap(&p->q[child], &p->q[parent]);
        bubble_up(p, parent);
    }
}

void bubble_down(priority_queue *p, int parent) {
    int child = left_child(parent);
    int min = parent; /* so far */

    for (int i = 0; i <= 1; i++) { /* test whether the left child or the right child is smaller than the parent */
        if ((child + i) <= p->n) { /* child exist */
            if (p->q[min].cost > p->q[child + i].cost) { /* parent is less than child */
                min = child + i;
            }
        }
    }
    if (min != parent) {
        swap(&p->q[child], &p->q[parent]);
        bubble_down(p, min);
    }
}

int extract_min(priority_queue *p) {
    int min = p->q[1].u;
    p->q[1].cost = p->q[p->n].cost; // bring n into position 1
    p->q[1].u = p->q[p->n].u;
    (p->n)--;
    bubble_down(p, 1);
    return min;
}

void pq_insert(priority_queue *p, int x, long int i) { /* O(log n) */
    (p->n)++;
    p->q[p->n].cost = i;
    p->q[p->n].u = x;
    bubble_up(p, p->n);
}
