//
// Reference: Algorithm Design Manual
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define QUEUESIZE 3

typedef struct queue {
    int buffer[QUEUESIZE];
    int first;
    int last;
    int count;
} queue;

void init_queue(queue *q) {
    q->first = 0;
    q->last = QUEUESIZE-1;
    q->count = 0;
}

void enqueue(queue *q, int x) {
    if (q->count >= QUEUESIZE) {
        printf("Warning: queue overflow enqueue x=%d\n", x);
    } else {
        q->last = (q->last+1) % QUEUESIZE;
        q->buffer[q->last] = x;
        q->count = q->count + 1;
    }
}

int dequeue(queue *q) {
    int x;
    if (q->count <= 0) {
        printf("Warning: empty queue dequeue.\n");
    } else {
        x = q->buffer[q->first];
        q->first = (q->first+1) % QUEUESIZE;
        q->count = q->count - 1;
    }
    return x;
}

int empty(queue *q) {
    return q->count <= 0;
}

void print_queue(queue *q) {
    int i;
    i = q->first;
    while (i != q->last) {
        printf("%c ",q->buffer[i]);
        i = (i+1) % QUEUESIZE;
    }
    printf("%2d ",q->buffer[i]);
    printf("\n");
}


int main() { /* test cases */
    queue *q = malloc(sizeof(queue));
    
    init_queue(q);
    enqueue(q, 1);
    enqueue(q, 2);
    
    printf("enqueue 1\n");
    printf("enqueue 2\n");
    
    printf("dequeue: %d\n", dequeue(q));
    
    enqueue(q, 4);
    printf("enqueue 4\n");
    enqueue(q, 5);
    printf("enqueue 5\n");
    
    printf("dequeue: %d\n", dequeue(q));
    return 0;
}
