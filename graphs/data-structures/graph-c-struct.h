//
// Reference: Algorithms Design Manual
// 2013
//
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAXV 1000 /* maximum number of vertices */

typedef struct edgenode {
    int y; /* adjacency info */
    int weight; /* edge weight, if any */
    struct edgenode *next; /* next edge in list */
} edgenode;

typedef struct graph {
    edgenode *edges[MAXV];
    int degree[MAXV]; /* outdegree of each vertex */
    int nvertices; /* number of vertices in the graph */
    int nedges; /* number of edges in the graph */
    bool directed; /* Is the graph directed? */
} graph;

void initialize_graph(graph *g, bool directed) {
    g->nvertices = 0;
    g->nedges = 0;
    g->directed = directed;

    for (int i = 0; i < MAXV; i++) {
        g->degree[i] = 0;
        g->edges[i] = NULL;
    }
}

void insert_edge(graph *g, int x, int y, int weight, bool directed) {
    edgenode *p = malloc(sizeof(edgenode));
    p->weight = weight; /* NULL */
    p->y = y;
    p->next = g->edges[x];
    g->edges[x] = p;
    g->degree[x]++;

    if (directed == false) {
        insert_edge(g, y, x, weight, true);
    } else {
        g->nedges++;
    }
}

void read_graph(graph *g) {
    int m, x, y;
    scanf("%d %d", &(g->nvertices), &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        insert_edge(g, x, y, 0, g->directed);
    }
}

void read_graph_with_weights(graph *g) {
    int m, x, y, weight;
    scanf("%d %d", &(g->nvertices), &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &weight);
        insert_edge(g, x, y, weight, g->directed);
    }
}

void print_graph(graph *g) {
    struct edgenode *p;
    for (int i = 0; i < g->nvertices; i++) {
        printf("%d: ", i);
        p = g->edges[i];
        while (p != NULL) {
            printf(" %d", p->y);
            p = p->next;
        }
        printf("\n");
    }
}
