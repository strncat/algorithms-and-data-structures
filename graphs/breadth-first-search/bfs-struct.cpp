//
// Reference: Algorithms Design Manual
// Simple Traversal with BFS
//

#include <iostream>
#include <queue>
#include <stdlib.h>

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

int distance[N];
int parent[N];

// distance holds shortest distance from start
// also distances are basically layers (layer 0, layer 1 and so on)
void BFS(graph *g, int start, int dest) {
    // init distance array
    for (int i = 0; i < g->nvertices; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    // queue for bfs
    std::queue<int> q;
    q.push(start);

    bool visited[N] = {false};
    distance[start] = 0;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        // found destination, we can stop or continue to find the rest of the shortest paths from start
        if (v == dest) {
            return;
        }

        edge *e = g->edges[v];
        while (e != NULL) {
            if (visited[e->y] == false) {
                q.push(e->y);
                distance[e->y] = distance[v] + 1;
                visited[v] = true;
                parent[e->y] = v;

            }
            e = e->next;
        }
    }
}

void find_path(int start, int end) { // shortest path
    if ((start == end) || (end == -1)) {
        printf("%d", start);
    } else {
        find_path(start, parent[end]);
        printf(" %d", end);
    }
}

int main() {
    // undirected graph
    graph g;
    g.nvertices = 4;
    insert(&g, 0, 2);
    insert(&g, 2, 0);
    insert(&g, 1, 2);
    insert(&g, 2, 1);
    insert(&g, 1, 3);
    insert(&g, 3, 1);
    print(&g);

    // run bfs to find if 3 can be reached from 0
    BFS(&g, 0, 3);
    printf("distance from 0 to 3 is %d\n", distance[3]);
    printf("path from 0 to 3 is\n");
    find_path(0, 3);
    printf("\n");
    return 0;
}
