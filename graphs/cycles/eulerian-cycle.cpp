//
//  Find the eulerian cycle in a graph
//
//  Created by FB on 04/20/20.
//  Copyright © 2020 nemo. All rights reserved.
//  Source: https://algs4.cs.princeton.edu/41graph/EulerianCycle.java
//  https://strncat.github.io/jekyll/update/2020/05/02/euler.html

#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>
#include <map>
#include <algorithm>
#include <sstream>
#include <set>
#include <stack>

typedef struct Edge {
    int v;
    int w;
    bool used;
    Edge(int v, int w) {
        this->v = v;
        this->w = w;
        this->used = false;
    }
} Edge;

int other_end(int v, Edge *e) {
    if (v == e->v) {
        return e->w;
    } else {
        return e->v;
    }
}

void dfs(std::vector<std::queue<Edge*>>& graph, std::set<int>& vertices) {
    std::stack<int> s;
    int start = *vertices.begin();
    s.push(start); // start with some vertex v
    std::stack<int> cycle; // the actual cycle

    while (!s.empty()) {
        int current_node = s.top(); s.pop(); // pick some node

        // now traverse it's edges
        while (!graph[current_node].empty()) {
            // (a) consider an edge between the current node and any of its neighbors
            Edge *edge = graph[current_node].front();
            graph[current_node].pop(); // remove the edge reference (it will still be in w's queue)

            // (b) if it's used then we'll check another. If it's not then mark it used
            if (edge->used) {
                continue;
            }
            edge->used = true; // mark it used

            // (c) push current_node back on the stack so we can go back to it (backtrack to it)
            s.push(current_node); // push current_node

            // (d) move to the other end of edge to process it
            current_node = other_end(current_node, edge);
        }
        // push the current_node which has no edges anymore to traverse
        cycle.push(current_node);
    }

    while (!cycle.empty()) {
        printf("%d ", cycle.top());
        cycle.pop();
    }
    printf("\n");
}

bool hasEulerCycle(std::vector<int>& degrees,
                   std::set<int>& vertices) {
    for (auto v = vertices.begin(); v != vertices.end(); v++) {
        if (degrees[*v] & 1) { //  odd
            return false;
        }
    }
    return true;
}

void init_graph(std::vector<std::queue<Edge*>>& graph,
                std::vector<int>& degrees,
                std::set<int>& vertices) {
    // prepare graph to have 6 nodes
    for (int i = 0; i <= 6; i++) {
        graph.push_back(std::queue<Edge*>());
        degrees.push_back(0);
    }

    vertices.insert(1); vertices.insert(2); vertices.insert(3);
    vertices.insert(4); vertices.insert(5); vertices.insert(6);

    Edge *e = new Edge(1,2);
    graph[1].push(e); graph[2].push(e);
    degrees[1]++; degrees[2]++;

    e = new Edge(2,3);
    graph[2].push(e); graph[3].push(e);
    degrees[2]++; degrees[3]++;

    e = new Edge(1,4);
    graph[1].push(e); graph[4].push(e);
    degrees[1]++; degrees[4]++;

    e = new Edge(5,3);
    graph[5].push(e); graph[3].push(e);
    degrees[5]++; degrees[3]++;

    e = new Edge(5,6);
    graph[5].push(e); graph[6].push(e);
    degrees[5]++; degrees[6]++;

    e = new Edge(2,6);
    graph[2].push(e); graph[6].push(e);
    degrees[2]++; degrees[6]++;

    e = new Edge(2,6);
    graph[2].push(e); graph[6].push(e);
    degrees[2]++; degrees[6]++;

    e = new Edge(4,6);
    graph[4].push(e); graph[6].push(e);
    degrees[4]++; degrees[6]++;
}

int main() {
    std::vector<std::queue<Edge*>> graph;
    std::vector<int> degrees;
    std::set<int> vertices;

    init_graph(graph, degrees, vertices);

    // every vertex must be of even degree, otherwise we don't have a cycle
    if (!hasEulerCycle(degrees, vertices)) {
        printf("An Eulerian Cycle doesn't exist\n");
    } else { // otherwise, we must have an Eulerian cycle
        dfs(graph, vertices); // find it
    }

    return 0;
}
