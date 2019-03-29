//
//  Programming Challenges
//  2013
//  queue.h
//

#include <stdio.h>
#include <stdbool.h>

#define QUEUESIZE 1000

typedef struct {
    int q[QUEUESIZE+1];	/* body of queue */
    int first;                      /* position of first element */
    int last;                       /* position of last element */
    int count;                      /* number of queue elements */
} queue;

void init_queue(queue *q) {
    q->first = 0;
    q->last = QUEUESIZE-1;
    q->count = 0;
}

void enqueue(queue *q, int x) {
    if (q->count < QUEUESIZE) {
        q->last = (q->last+1) % QUEUESIZE;
        q->q[ q->last ] = x;
        q->count = q->count + 1;
    }
}

int dequeue(queue *q) {
    int x = q->q[ q->first ];
    q->first = (q->first+1) % QUEUESIZE;
    q->count = q->count - 1;
    return x;
}

int empty_queue(queue *q) {
    if (q->count <= 0) return (true);
    else return (false);
}
