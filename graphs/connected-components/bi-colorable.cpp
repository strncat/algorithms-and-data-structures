//
// Reference: Algorithms Design Manual
// 2-Color with BFS
//

#include <iostream>
#include <queue>
#include <stdlib.h>
#include <assert.h>

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

#define UNCOLORED 0
#define WHITE 1
#define BLACK 2

int complement(int color) {
    if (color == WHITE) return(BLACK);
    if (color == BLACK) return(WHITE);
    return(UNCOLORED);
}

bool process_edge(int x, int y, int *color) {
    if (color[x] == color[y]) {
        return false;
    }
    color[y] = complement(color[x]);
    return true;
}

bool bfs(graph *g, int start, int *color, bool *discovered, bool *processed) {
    // queue for bfs
    std::queue<int> q;
    q.push(start);
    discovered[start] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        processed[v] = true;

        edge *e = g->edges[v];
        while (e != NULL) {
            int y = e->y;
            if (processed[y] == false) {
                if (process_edge(v, y, color) == false) {
                    return false;
                }
            }
            if (discovered[y] == false) {
                q.push(y);
                discovered[y] = true;
            }
            e = e->next;
        }
    }
    return true;
}

bool two_color(graph *g) {
    int color[N];
    bool discovered[N];
    bool processed[N];

    for (int i = 0; i < g->nvertices; i++) {
        processed[i] = discovered[i] = false;
        color[i] = UNCOLORED;
    }

    for (int i = 0; i < g->nvertices; i++) { /* for every component */
        if (discovered[i] == false) {
            color[i] = WHITE;
            if (bfs(g, i, color, discovered, processed) == false) { /* not colorable */
                return false;
            }
        }
    }
    return true;
}

void test() {
    // test 1
    graph g;
    g.nvertices = 3;
    insert(&g, 0, 1);
    insert(&g, 1, 0);
    insert(&g, 1, 2);
    insert(&g, 2, 1);
    insert(&g, 0, 2);
    insert(&g, 2, 0);
    assert(two_color(&g) == false); // not bicolorable

    // test 2
    graph m;
    m.nvertices = 4;
    insert(&m, 0, 1);
    insert(&m, 1, 0);
    insert(&m, 0, 3);
    insert(&m, 3, 0);
    assert(two_color(&m) == true); // colorable
}

int main() {
    test();
    return 0;
}
