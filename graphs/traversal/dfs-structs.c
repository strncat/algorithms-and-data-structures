//
// Simple DFS in C
// with path finding example https://github.com/fbroom/competitive-programming/blob/master/hacker-rank/artificial-intelligence/a-star-search/pacman-dfs.cpp
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../data-structures-c/graph.h"
#include "../data-structures-c/stack.h"

void initialize_search(graph *g, int *discovered) {
    for (int i = 1; i <= g->nvertices; i++)
        discovered[i] = 0;
}

void process_vertex(int v) {
    printf(" %d", v);
}

// explicit stack
void dfs(graph *g, int start, int *discovered) {
    stack s;
    init_stack(&s);
    push(&s, start);
    discovered[start] = 1;

    while(is_stack_empty(&s) == 0) {
        int v = pop(&s);
        process_vertex(v);
        edgenode *p = g->edges[v];

        while (p != NULL) {
            int y = p->y;
            if (discovered[y] == 0) {
                push(&s, y);
                discovered[y] = 1;
            }
            p = p->next;
        }
    }
}

void dfsRecursive(graph *g, int start, int *discovered) {
    discovered[start] = 1;
    process_vertex(start);
    edgenode *p = g->edges[start];

    while (p != NULL) {
        int y = p->y;
        if (discovered[y] == 0) {
            dfsRecursive(g, y, discovered);
            discovered[y] = 1;
        }
        p = p->next;
    }
}

void tests() {
    // TODO
}

int main() {
    graph *g = malloc(sizeof(graph));
    initialize_graph(g, false);
    read_graph(g);
    print_graph(g);
    return 0;
}
