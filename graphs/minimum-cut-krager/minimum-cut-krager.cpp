//
//  Randomized Contraction Algorithm  For The Min Cut Problem by Karger O(mn^2)
//  Implementation based on the best algorithms lectures from Tim Roughgarden
//
//  definitely needs improvement I waste space and most likely time too
//  very slow for 200 nodes!
//
//  Created by Fatima B on 10/30/15.
//  Copyright © 2015 nemo. All rights reserved.
//

#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#include <assert.h>

class Graph {
public:
    int nvertices; // number of vertices
    std::list<int> *adj; // adjaceny list so that it is easy to find out what neighbors are connected to a node
    std::vector<std::pair<int,int>> edges;
    // why another vector of edges? because for the min cut algorithm
    // I want to pick an edge at random, wasn't sure how to do it with the adjaceny list
    // this is where I'm wasting space
    std::vector<bool> active; // current nodes
    Graph(int v) {
        nvertices = v;
        adj = new std::list<int>[v + 1];
        for (int i = 0; i <= nvertices; i++) {
            active.push_back(true);
        }
    }

    Graph(const Graph& g) { // copy constructor
        nvertices = g.nvertices;
        adj = new std::list<int>[g.nvertices + 1];
        edges.insert(edges.end(), g.edges.begin(), g.edges.end());
        for (int i = 1; i <= nvertices; i++) {
            adj[i].insert(adj[i].end(), g.adj[i].begin(), g.adj[i].end());
        }
        for (int i = 0; i <= nvertices; i++) {
            active.push_back(g.active[i]);
        }
    }

    void insert_edge(int v, int u) {
        adj[v].push_back(u);
        edges.push_back(std::make_pair(v, u));
    }

    void remove_edge(int v, int u) {
        adj[v].remove(u);
        edges.erase(std::remove(edges.begin(), edges.end(),
                                std::make_pair(v, u)), edges.end());
    }

    // this is the core of the algorithm
    // for the randomely picked edges, merge both into one
    void merge_nodes(int v, int u) { // merge u into v
        // (1) delete the edge between v and u
        remove_edge(v, u);
        remove_edge(u, v);

        // and then go through the edges connected to u
        std::list<int> l = adj[u];
        for (auto i = l.begin(); i != l.end(); i++) {
            if (*i == v) { // (a) self loop, don't insert it, just ignore it
                continue;
            }
            insert_edge(v, *i); // (b) now they are connected to v instead
            insert_edge(*i, v);

            remove_edge(u, *i); // (c) remove all edges from the original node
            remove_edge(*i, u);
        }
        active[u] = false;
    }

    void print() {
        for (int i = 1; i <= nvertices; i++) {
            if (!active[i]) {
                continue;
            }
            printf("%d: ", i);
            std::list<int> l = adj[i];
            for (auto i = l.begin(); i != l.end(); i++) {
                printf("%d ", *i);
            }
            printf("\n");
        }
        printf("\n");
    }
};

int trial(Graph g) { // each trial
    int count = 0;
    while (1) {
        if (count == g.nvertices - 2) { break; } // stop when we have two nodes

        int e = rand() % g.edges.size(); // pick an edge at random
        int r = g.edges[e].first;
        int s = g.edges[e].second;

        count++;
        g.merge_nodes(r, s); // merge the two nodes
    }
    return (int)g.edges.size()/2; // the size of the min cut (this is an weighted graph)
}

int min_cut(Graph g) { // start point of the algorithm
    int min = INT_MAX, current;

    // try it for n^2 times .. why? watch the lectures for the proof (beautiful proof)
    for (int i = 0; i < g.nvertices*g.nvertices; i++) {
        srand (unsigned (time (NULL)));
        Graph copy(g);
        current = trial(copy);
        printf("min cut is %d\n", current);
        if (current < min) {
            min = current;
        }
    }
    printf("best min cut is %d\n", min);
    return min;
}

void tests() {
    Graph g(8); // we have 8 vertices
    std::ifstream file("test1.txt");
    if (!file) { return; }
    char line[1000];
    while(file) {
        file.getline(line, 10000); // delim defaults to '\n'
        std::stringstream stream(line);
        int v;
        stream >> v; // root
        while(1) { // neighbors or connections
            int y;
            stream >> y;
            if(!stream) {
                break;
            }
            g.insert_edge(v, y);
        }
    }
    file.close();
    int min = min_cut(g);
    assert(min == 2);
}

int main() {
    tests();
    return 0;
}
