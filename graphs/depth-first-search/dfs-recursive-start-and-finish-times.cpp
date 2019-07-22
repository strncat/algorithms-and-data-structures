//
//  DFS - Depth First Search (with start/finish times)
//
//  Created by FB on 7/6/19.
//  Copyright © 2019 FB. All rights reserved.
//

#include <iostream>
#include <vector>

int dfs(int v, int current_time,
        std::vector<std::vector<int>>& graph,
        std::vector<std::pair<int,int>> &times,
        std::vector<int> &visited) {

    times[v].first = current_time++; // seeing v for the first time
    visited[0] = true;

    for (int i = 0; i < graph[v].size(); i++) {
        int u = graph[v][i];
        if (visited[u] == false) {
            current_time = dfs(u, current_time, graph, times, visited);
            current_time++;
        }
    }
    times[v].second = current_time; // v is done bye forever
    return current_time;
}

int main() {
    std::vector<std::vector<int>> graph(5);
    graph[0].push_back(1);
    graph[1].push_back(2);
    graph[2].push_back(3);
    graph[3].push_back(4);

    // vector to keep track of (start time, finish time) for each vertex
    std::vector<std::pair<int,int>> times(5);

    // vector to track visited status
    std::vector<int> visited(5);
    for (int i = 0; i < graph.size(); i++) {
        visited.push_back(false);
    }
    printf("%d\n", dfs(0, 0, graph, times, visited));
    return 0;
}
