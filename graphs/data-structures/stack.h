//
//  Reference: Programming Challenges
//  2013
//

#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>

#define STACKSIZE 10000

typedef struct {
    int array[STACKSIZE+1];
    int count;
} stack;

void init_stack(stack *s) {
    s->count = 0;
}

void push(stack *s, int x) {
    if (s->count < STACKSIZE) {
        s->array[s->count] = x;
        s->count++;
    }
}

int pop(stack *s) {
    int x = 0;
    if (s->count > 0) {
        x = s->array[s->count-1];
        s->count--;
    }
    return x;
}

int is_stack_empty(stack *s) {
    return (s->count == 0);
}
