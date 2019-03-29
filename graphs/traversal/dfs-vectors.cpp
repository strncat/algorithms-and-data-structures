//
//  DFS - vectors
//

#include <iostream>
#include <stack>
#include <vector>

using std::vector;

int dfs(int start, std::vector<vector<int>>& graph) {
    std::stack<int> s;
    s.push(start);

    vector<int> visited;
    for (int i = 0; i < graph.size(); i++) {
        visited.push_back(false);
    }
    visited[start] = true;

    int total = 0;
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        total++;
        for (int i = 0; i < graph[v].size(); i++) {
            int u = graph[v][i];
            if (visited[u] == false) {
                s.push(u);
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

    printf("%d\n", dfs(0, graph));
    return 0;
}
