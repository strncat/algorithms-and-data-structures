//
//  Kruskal
//
//  Description and Proof
//  https://strncat.github.io/jekyll/update/2019/04/03/kruskal.html
//
//  Algorithm:
//  - initialize V sets where the leader of each set is just the vertex itself.
//  - initialize a set to hold the minimum spanning tree.
//  - sort all edges in the graph
//  - and we go through all edges in a loop
//  - if both x and y are in different sets (they don't have the same leader) then
//    we can add this edge to the MST and combine both sets
//
//  Runtime:
//  - The time to make each in the begining is just O(V).
//  - the time to sort the edges is O(ElgE)
//  - We perform 2*E FIND-SET so that's O(Elg(V)) and (V-1) UNION operations in O(V).
//  - The total time is then O(ElgE) = O(ElgV) which is similar to Prim
//
//  Practice Problem: https://www.hackerrank.com/challenges/kruskalmstrsub

#include <iostream>
#include <vector>
#include <queue>
#include <assert.h>
#include <algorithm>

class Edge {
public:
    int x;
    int y;
    int weight;
    Edge(int x, int y, int weight) {
        this->x = x;
        this->y = y;
        this->weight = weight;
    }
    bool operator<(const Edge &e) const { return weight < e.weight; }
};

class Graph {
public:
    std::vector<Edge> edges;
    int nvertices;
    Graph(int nvertices) {
        this->nvertices = nvertices;
    }
    void insertEdge(int x, int y, int weight) {
        edges.push_back(Edge(x, y, weight));
    }
};


class UnionByRank {
public:
    int *leader;
    int *rank;
    int n;
    int count;
    UnionByRank(int n) {
        this->n = n;
        count = n; // initially the number of components is n
        leader = new int[n];
        rank = new int[n];
        for (int i = 1; i <= n; i++) {
            leader[i] = i; // each item is in its own component
            rank[i] = 0;
        }
    }
    int findOP(int x) { // O(log*(n))
        while (leader[x] != x) { // go up the tree
            leader[x] = leader[leader[x]]; // path compression
            x = leader[x];
        }
        return x;
    }
    int connected(int x, int y) {
        return findOP(x) == findOP(y);
    }

    // for Kruskal though we have the findOP already
    // so we should just pass it
    void unionOP(int rootX, int rootY) {
        if (rootX == rootY) { return; }
        if (rank[rootX] <= rank[rootY]) {
            leader[rootX] = rootY;
            rank[rootY]++;
        } else {
            leader[rootY] = rootX;
            rank[rootX]++;
        }
        count--;
    }
};

std::vector<Edge> kruskal(Graph &g) { // O(ElogE) m is the number of edges
    UnionByRank u = UnionByRank(g.nvertices);
    std::vector<Edge> mst; // extra space to preserve the graph
    std::sort(g.edges.begin(), g.edges.end()); // O(ElogE)

    for (auto t = g.edges.begin(); t!= g.edges.end(); t++) {
        int rootX = u.findOP(t->x); // log(V)
        int rootY = u.findOP(t->y); // log(V)
        if (rootX != rootY) {
            u.unionOP(rootX, rootY); // calling this at most V-1 times => O(V)
            mst.push_back(*t);
        }
    }
    return mst;
}

int main() {
    Graph g = Graph(5);
    g.insertEdge(1, 2, 3);
    g.insertEdge(1, 5, 1);
    g.insertEdge(2, 3, 5);
    g.insertEdge(2, 5, 4);
    g.insertEdge(3, 5, 6);
    g.insertEdge(3, 4, 2);
    g.insertEdge(4, 5, 7);
    std::vector<Edge> mst = kruskal(g);
    for (auto t = mst.begin(); t != mst.end(); t++) {
        std::cout << t->x << " " << t->y << " " << t->weight << std::endl;
    }
    std::cout << std::endl;
    return 0;
}


