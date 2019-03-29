//
// Finding Cycles with DFS in C++
// Reference: Algorithms Design Manual
// 2014
//
//

#include <iostream>
#include <stack>
#include <stdlib.h>
#include <assert.h>

#define N 100

typedef struct edge {
    int y;
    struct edge *next;
} edge;

typedef struct graph {
    edge *edges[N];
    int nvertices;
    bool directed;
} graph;

typedef struct dfsData {
    bool discovered[N], processed[N];
    int parent[N], entry_time[N], exit_time[N];
    int time;
    dfsData() {
        time = 0;
        for (int i = 1; i <= N; i++) {
            discovered[i] = processed[i] = false;
            parent[i] = entry_time[i] = exit_time[i] = -1;
        }
    }
} dfsData;

void insert(graph *g, int node, int neighbor) {
    edge *e = (edge*) malloc(sizeof(edge));
    e->y = neighbor;
    e->next = g->edges[node];
    g->edges[node] = e; // insert at the front of the edges
}

void print(graph *g) { // print graph
    for (int i = 1; i <= g->nvertices; i++) {
        printf("%d: ", i);
        edge *temp = g->edges[i];
        while (temp != NULL) {
            printf("%d ", temp->y);
            temp = temp->next;
        }
        printf("\n");
    }
}

void process_edge(int v, int y, dfsData *data) {
    // if parent[v] == y it means we're visitng the same edge since this is unweighted?
    // y must be discovered otherwise this is the first I'm seeing it?
    if (data->discovered[y] && data->parent[v] != y) {
        printf("\nfound a back edge (%d %d) \n", v, y);
    }
}

void dfs(graph *g, int v, dfsData *data) {
    // (1) arly processing
    data->discovered[v] = true;
    data->time++;
    data->entry_time[v] = data->time;

    // (2) recursively visit kids
    edge *e = g->edges[v];
    while (e != NULL) {
        int y = e->y;
        if (data->discovered[y] == false) {
            data->parent[y] = v;
            dfs(g, y, data);
        } else if (!data->processed[y] || g->directed) { // does g->directed make sense for directed graphs?
                                                          // unprocessed is only needed for directed graphs
            process_edge(v, y, data);
        }
        e = e->next;
    }

    // (2) late processing
    data->time++;
    data->exit_time[v] = data->time;
    data->processed[v] = true;
}

void tests() {
    //
}

int main() {
    // undirected graph
    graph *g = (graph*) malloc(sizeof(graph));
    g->nvertices = 6;

    // Example 1 undirected (5, 2) is a back edge
    // g->directed = false;
    //insert(g, 1, 2); insert(g, 2, 1); insert(g, 1, 6); insert(g, 6, 1);
    //insert(g, 5, 2); insert(g, 2, 5); insert(g, 2, 3); insert(g, 3, 2);
    //insert(g, 4, 5); insert(g, 5, 4); insert(g, 4, 3); insert(g, 3, 4);

    // Example 2 undirected no cycle here, remember this is unweighted
    // g->directed = false;
    //insert(g, 5, 2); insert(g, 2, 5);

    // Example 3 directed graph
    g->directed = true;
    insert(g, 1, 2); insert(g, 2, 3); insert(g, 3, 4);
    insert(g, 4, 5); insert(g, 5, 6); insert(g, 6, 3);


    print(g);
    dfsData *data = new dfsData();
    dfs(g, 1, data);
    printf("\n");
    //print(data->entry_time, g->nvertices);
    //print(data->exit_time, g->nvertices);
    return 0;
}
