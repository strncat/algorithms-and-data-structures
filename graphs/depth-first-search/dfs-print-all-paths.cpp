//
//  Print all paths in a graph using DFS
//
//  Created by FB on 10/19/17.
//  Copyright © 2017 FB. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

typedef std::vector<std::vector<int>> graph;

void print(int *distance, long n) {
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; i++) {
        printf("%d \t\t %d\n", i, distance[i]);
    }
}

void print_path(std::vector<int> parent, int dest) {
    if (parent[dest] != -1) {
        print_path(parent, parent[dest]);
    }
    printf("%d ", dest);
}

void dfs(graph& g, std::vector<int> &visited, std::vector<int> &parent, int u, int dest) {
    if (u == dest) {
        print_path(parent, dest);
        printf("\n");
        return;
    }

    for (int i = 0; i < g[u].size(); i++) {
        int neigbhor = g[u][i];
        if (visited[neigbhor] == false) {
            visited[neigbhor] = true;
            parent[neigbhor] = u;
            dfs(g, visited, parent, neigbhor, dest);
            visited[neigbhor] = false;
            parent[neigbhor] = -1;
        }
    }
}

void dfs_init(graph &g, int source, int dest) {
    std::vector<int> visited;
    std::vector<int> parent;
    for (int i = 0; i < g.size(); i++) {
        visited.push_back(false);
        parent.push_back(-1);
    }
    visited[source] = true;
    dfs(g, visited, parent, source, dest);
}

int main() {
    graph g;
    for (int i = 0; i < 7; i++) {
        g.push_back(std::vector<int>());
    }
    g[0].push_back(1);
    g[1].push_back(0);

    g[0].push_back(2);
    g[2].push_back(0);

    g[0].push_back(3);
    g[3].push_back(0);

    g[1].push_back(3);
    g[3].push_back(1);

    g[1].push_back(4);
    g[4].push_back(1);

    g[2].push_back(3);
    g[3].push_back(2);

    g[2].push_back(5);
    g[5].push_back(2);

    g[3].push_back(6);
    g[6].push_back(3);

    g[4].push_back(6);
    g[6].push_back(4);

    g[5].push_back(6);
    g[6].push_back(5);

    dfs_init(g, 0, 6);
    return 0;
}
