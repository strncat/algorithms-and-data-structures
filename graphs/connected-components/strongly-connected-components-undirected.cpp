//
// Reference: Algorithms Design Manual
// Find strongly connected components in an undirected graph with bfs
//

#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <queue>

#define N 100

typedef struct edge {
    int y;
    int weight; // optional
    struct edge *next;
} edge;

typedef struct graph {
    edge *edges[N];
    int nvertices;
} graph;

void insert(graph *g, int x, int y) {
    edge *e = (edge*) malloc(sizeof(edge));
    e->y = y;
    e->next = g->edges[x];
    g->edges[x] = e; // insert at the front of the edges
}

void print(graph *g) {
    for (int i = 0; i < g->nvertices; i++) {
        printf("%d: ", i);
        edge *temp = g->edges[i];
        while (temp != NULL) {
            printf("%d ", temp->y);
            temp = temp->next;
        }
        printf("\n");
    }
}

void bfs(graph *g, int start, bool *discovered) {
    // queue for bfs
    std::queue<int> q;
    q.push(start);

    discovered[start] = true;

    while(!q.empty()) {
        int v = q.front();
        q.pop();

        printf("%d ", v);

        edge *p = g->edges[v];

        while (p != NULL) {
            int y = p->y;
            if (discovered[y] == false) {
                q.push(p->y);
                discovered[y] = true;
            }
            p = p->next;
        }
    }
}

void strongly_connected_components(graph *g) {
    bool discovered[N];
    for (int i = 0; i < g->nvertices; i++) {
        discovered[i] = false;
    }

    int c = 0;
    for (int i = 0; i < g->nvertices; i++)
        if (discovered[i] == false) {
            c++;
            printf("Component %d: ", c);
            bfs(g, i, discovered);
            printf("\n");
        }
}

int main() {
    // initialize graph
    graph g;
    g.nvertices = 4;
    insert(&g, 0, 2);
    insert(&g, 2, 0);
    insert(&g, 1, 2);
    insert(&g, 2, 1);
    print(&g);

    // find the strongly connected components using bfs
    strongly_connected_components(&g);
    return 0;
}
