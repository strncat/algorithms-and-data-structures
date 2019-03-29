//
//  Minimum Spaning Trees - Prim
//  Algorithm Design Manual and Algorithms - Stanford (Coursera)
//  2014
//

#include <iostream>
#include <queue>
#include "../data-structures-c++/graph.h"

struct comparator {
    bool operator() (std::pair<int, int> i, std::pair<int, int> j) { return i.second > j.second; }
};

void printArray(int *a, int n) {
    for (int i = 1; i <= n; i++) { printf("%d ", a[i]); } printf("\n");
}

int prim(Graph& g) { // O(|E|log|V|) if g is dense, E = V^2
    // initialization
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, comparator> minHeap;
    int *parent = new int[g.nvertices + 1]; // to construct the MST
    int *visited = new int[g.nvertices + 1]; // marker array
    int *key = new int[g.nvertices + 1];

    /* How does the key get updated?
     
      {min -----2----- v
      span             |
      ning             1
      tree}            |
         ------10 -----w

     let v and w be the only vertices left to be picked by the MST (let there be an edge of length 1 between v and w)
     let the available edges for v that connects v into the current MST be of length 2, 5, 7, so key[v] = 2
     let the available edges for w that connects w into the current MST be of length 10, so key[w] = 10
     Now between v and w we pick v (lowest node in the minHeap key[v] < key[w]), v is now part of the MST
     when we visit v's neigbhor w, note that w's key should now be 1 instead of 10, because we added a new node to the MST v which
     makes accessing w cheaper, so as we visit those edges, we update the key whenever key[neighbor] > key[v]
     it will also have to be unvisited not to violate the MST condition
     for w, key[w] = 10 but v-w is only of length 1 and so we update key[w] = 1
     */

    for (int i = 1; i <= g.nvertices; i++) {
        visited[i] = false;
        key[i] = INT_MAX;
        parent[i] = -1;
    }

    key[1] = 0; // let the start node be node 1
    minHeap.push(std::make_pair(1, key[1]));

    // core
    while(!minHeap.empty()) {
        int v = minHeap.top().first;
        minHeap.pop();
        visited[v] = true;

        std::list<Edge> p = g.adj[v];
        for (auto e = p.begin(); e != p.end(); e++) { // pick the cheapest edge
            int w = e->y;
            int weight = e->weight;
            if (key[w] > weight && visited[w] == false) { // w can be connected to the MST in a cheaper way, it has to also be an univisited node
                key[w] = weight;
                parent[w] = v;
                // I should though delete the older edge from the heap! (The C Implementation implements a decrease key operation)
                minHeap.push(std::make_pair(w, key[w]));
            }
        }
    }

    // post-processing
    int totalCost = 0;
    for (int i = 1; i <= g.nvertices; i++) {
        totalCost += key[i];
    }
    delete key;
    delete parent;
    return totalCost;
}

int main() {
    FILE *fp = fopen("edges.txt", "r");
    if (fp == NULL) { return 0; }
    int vertices, edges, v, u, weight;

    fscanf(fp, "%d %d", &vertices, &edges); // number of vertices, edges

    Graph g = Graph(vertices);

    for (int i = 0; i < edges; i++) {
        fscanf(fp, "%d %d %d", &v, &u, &weight);
        g.insertEdge(v, u, weight);
        g.insertEdge(u, v, weight);
    }
    fclose(fp);
    //g.print();
    int cost = prim(g);
    printf("minimum spanning tree is of cost = %d\n", cost);
    return 0;
}
