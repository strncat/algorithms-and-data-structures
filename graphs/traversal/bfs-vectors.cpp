//
//  BFS - vectors
//

#include <iostream>
#include <queue>
#include <vector>

using std::vector;

int bfs(int start, std::vector<vector<int>>& graph) {
    std::queue<int> q;
    q.push(start);

    vector<int> visited;
    for (int i = 0; i < graph.size(); i++) {
        visited.push_back(false);
    }
    visited[start] = true;

    int total = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        total++;
        for (int i = 0; i < graph[v].size(); i++) {
            int u = graph[v][i];
            if (visited[u] == false) {
                q.push(u);
                visited[u] = true;
            }
        }
    }
    return total;
}

int main() {
    std::vector<vector<int>> graph(3);

    graph[0].push_back(1);
    graph[1].push_back(0);
    graph[0].push_back(2);
    graph[2].push_back(0);

    printf("%d\n", bfs(0, graph));
    return 0;
}