//
// Reference: Algorithms Design Manual
// Find the shortest paths with BFS from a start node to every other node
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

// find the shortest paths from the start node to every other node
void bfs(graph *g, int start) {
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

// recover the path if needed using the parents array
void find_path(int start, int end) {
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
    print(&g);

    // shortested paths from 0 from every other node
    bfs(&g, 0);
    printf("shortest paths are\n");
    for (int i = 0; i < g.nvertices; i++) {
        printf("%d ", distance[i]);
    }
    printf("\n");
    return 0;
}
