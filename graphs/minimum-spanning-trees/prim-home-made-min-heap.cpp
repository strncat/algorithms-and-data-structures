//
// Implementation of Prim using a custom Minimum Heap
//
//  Algorithm:
//  We explore all the elements in the minimum heap until it's empty
//  We pop a node v and mark it as visited.
//  We look at all the unvisited neigbors of v. For each neigbor y:
//  we check if edgeWeight[v->y] < distance[y]. Meaning, will this new edge (v,y) connect me to y in a cheaper way than the current edge?
//  We add y to the minimum heap but If y already exists, then we need to decrease its value in the minimum heap. (look at the implementation details for more details)
//
//  Running Time
//  Each EXTRACT-MIN operation takes O(lgV) time, the total time for all calls to EXTRACT-MIN is O(VlgV).
// We look at each edge in Prim at most twice when visiting the unvisited neigbors therefore the runing time for looking at all edges is O(E)
// "The DECREASE-KEY operation on the min-heap, which a binary min-heap supports in O(lgV) time"
// The total time for Prim’s algorithm is O(VlgV + ElgV) = O(ElgV)"
// By using Fibonacci heaps, Prim’s algorithm runs in time O(E + VlgV), which improves over the binary-heap implementation if |V| is much smaller than |E|

//My implementation of decrease-key on a heap is slow because I do a linear search
//to find the node and then call bubble up. I should at least maintain pointers
//to the nodes in the heap so that I call bubble up right away without search.
//In CRLS however, it is noted that "We can in fact achieve a running time of
//O(Vlg(V) + E) by implementing the min-priority queue with a **Fibonacci heap**
//(see Chapter 19). The amortized cost of each of the |V| EXTRACT-MIN operations
//is O(lgV) , **and each DECREASE KEY call, of which there are at most |E|,
//takes only O(1)** [huh!] amortized time. Historically, the development of
//Fibonacci heaps was motivated by the observation that Dijkstra’s algorithm
//typically makes many more DECREASE-KEY calls than EXTRACT-MIN calls,"

#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>

#define PQ_SIZE 100000

struct min_heap {
    int nodes[PQ_SIZE+1];
    int values[PQ_SIZE+1];
    int n;
};

void init_heap(min_heap *q) {
    q->n = 0;
}

bool empty(min_heap *q) {
    return (q->n == 0);
}

int left_child(int parent) {
    return (2 * parent);
}

int right_child(int parent) {
    return (2 * parent) + 1;
}

int get_parent(int child) {
    if (child == 1) {
        return -1;
    }
    return child/2;
}

void swap(int *a, int *b) {
    int temp = *b;
    *b = *a;
    *a = temp;
}

void bubble_up(min_heap *q, int child) {
    int parent = get_parent(child);
    if (parent == -1) {
        return;
    } else if (q->values[parent] > q->values[child]) {
        swap(&q->values[child], &q->values[parent]);
        swap(&q->nodes[child], &q->nodes[parent]);
        bubble_up(q, parent);
    }
}

void bubble_down(min_heap *q, int parent) {
    int child = left_child(parent);
    int min = parent;

    for (int i = 0; i <= 1; i++) {
        if ((child + i) <= q->n) {
            if (q->values[min] > q->values[child + i]) {
                min = child + i;
            }
        }
    }
    if (min != parent) {
        swap(&q->values[min], &q->values[parent]);
        swap(&q->nodes[min], &q->nodes[parent]);
        bubble_down(q, min);
    }
}

int extract_min(min_heap *q) {
    //int minimum = q->values[1];
    int minimum_node = q->nodes[1];

    q->values[1] = q->values[q->n];
    q->nodes[1] = q->nodes[q->n];

    (q->n)--;
    bubble_down(q, 1);
    return minimum_node;
}

void insert(min_heap *q, int node, int value) {
    (q->n)++;
    q->values[q->n] = value;
    q->nodes[q->n] = node;
    bubble_up(q, q->n);
}

// THIS LINEAR SEARCH IS BAD .. WE SHOULD MAINTAIN ANOTHER ARRAY OF POINTERS TO
// THE NODES IN THE HEAP SO THAT DECREASE-KEY is LG(N)
void decrease_key(min_heap *q, int node, int value) {
    for (int i = 1; i <= q->n; i++) {
        if (q->nodes[i] == node) {
            q->values[i] = value;
            bubble_up(q, i); // bubble it up!
        }
    }
}

#define N 5000

typedef struct edge {
    int y;
    int weight;
    edge *next;
} edge;

typedef struct graph {
    int nvertices;
    edge *edges[N]; // pointers to edges
} graph;

void init_graph(graph *g, int n) {
    g->nvertices = n;
    for (int i = 1; i <= n; i++) {
        g->edges[i] = NULL;
    }
}

void insert(graph *g, int x, int y, int weight) {
    edge *e = new edge();
    e->y = y;
    e->weight = weight;
    e->next = g->edges[x];
    g->edges[x] = e;
}

int dijkstra(graph *g, int start) {
    // INIT DISTANCE ARRAY
    int distance[N];
    int visited[N];
    for (int i = 1; i <= g->nvertices; i++) {
        distance[i] = INT_MAX;
        visited[i] = 0;
    }

    // INIT MIN_HEAP AND INSERT START NODE
    min_heap h;
    init_heap(&h);
    distance[start] = 0;
    insert(&h, start, distance[start]);

    while (!empty(&h)) {
        int node = extract_min(&h);
        visited[node] = 1; // WE WON'T CHECK THIS NODE EVER AGAIN

        edge *e = g->edges[node];
        while (e != NULL) {
            if (!visited[e->y]) {
                // THE ONLY DIFFERENCE BETWEEN DIJKSTRA AND PRIM IS THE RELAXING CONDITION
                if (distance[e->y] > e->weight) {
                    if (distance[e->y] == INT_MAX) { // FIRST TIME
                        distance[e->y] = e->weight;
                        insert(&h, e->y, distance[e->y]);
                    } else {
                        // KEY ALREADY EXIST, UPDATE ITS VALUE
                        distance[e->y] = e->weight;
                        decrease_key(&h, e->y, distance[e->y]);
                    }
                }
            }
            e = e->next;
        }
    }
    int sum = 0;
    for (int i = 1; i <= g->nvertices; i++) {
        sum += distance[i];
    }
    return sum;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    graph g;
    int x, y, weight, start;
    init_graph(&g, n);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &weight);
        insert(&g, x, y, weight);
        insert(&g, y, x, weight);
    }
    scanf("%d", &start);
    printf("%d\n", dijkstra(&g, start));
    return 0;
}
