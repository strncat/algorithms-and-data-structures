#include <stdio.h>
#include <stdlib.h>

#define N 100

typedef struct stack {
    int buffer[N];
    int top;
} stack;

void push(stack *s, int item) {
    if (s->top == N) {
        return;
    }
    s->buffer[s->top++] = item;
}

int pop(stack *s) {
    if (s->top == 0) {
        return -1; /* ERROR */
    }
    return s->buffer[--s->top];
}

void init(stack *s) {
    s->top = 0;
}

int empty(stack *s) {
    return (s->top == 0);
}

int main() {
    stack *s = malloc(sizeof(stack));
    
    init(s);
    push(s, 1);
    push(s, 2);
    push(s, 3);
    
    printf("%d\n", pop(s));
    printf("%d\n", pop(s));
    printf("%d\n", pop(s));
    return 0;
}
