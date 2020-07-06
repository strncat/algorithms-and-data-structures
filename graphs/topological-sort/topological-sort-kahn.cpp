//
//  main.cpp
//  kahn
//
//  Created by strncat on 7/5/20.
//

#include <iostream>
#include <queue>
#include <vector>

void kahn(std::vector<std::vector<int>> &g) {
    std::vector<int> in_degree(g.size(), 0);
    std::queue<int> q;

    // compute the in-degree of each vertex in O(E+V)
    for (int u = 0; u < g.size(); u++) {
        for (int i = 0; i < g[u].size(); i++) {
            int neighbor = g[u][i];
            in_degree[neighbor]++;
        }
    }

    for (int u = 0; u < g.size(); u++) {
        if (in_degree[u] == 0) {
            q.push(u);
        }
    }

    std::vector<int> ordered_vertices;
    while (!q.empty()) {
        int u = q.front(); // some vertex with in-degree = 0
        q.pop();
        ordered_vertices.push_back(u);

        // decrease all neighbors
        for (int i = 0; i < g[u].size(); i++) {
            int neighbor = g[u][i];
            in_degree[neighbor]--;
            if (in_degree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    // cycle check
    if (ordered_vertices.size() != g.size()) {
        printf("cycle!!!!!\n");
        return;
    }

    for (int i = 0; i < ordered_vertices.size(); i++) {
        printf("%d\n", ordered_vertices[i]);
    }
    printf("\n");
}

int main(int argc, const char * argv[]) {
    std::vector<std::vector<int>> graph(6, std::vector<int>());
    graph[5].push_back(2);
    graph[5].push_back(0);
    graph[4].push_back(0);
    graph[4].push_back(1);
    graph[2].push_back(3);
    graph[3].push_back(1);
    kahn(graph);
    return 0;
}
