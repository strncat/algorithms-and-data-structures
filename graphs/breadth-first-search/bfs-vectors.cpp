//
//  BFS - vectors
//

#include <iostream>
#include <queue>
#include <vector>

int bfs(int start, int end, std::vector<std::vector<int>>& graph) {
    std::queue<int> q;
    q.push(start);
    // another queue to push the distances down (bfs works in layers)
    std::queue<int> qd;
    qd.push(0);
    // visited array so we don't revisit nodes
    std::vector<int> visited(graph.size(), false);
    visited[start] = true;
    // parent array to print the path
    std::vector<int> parent(graph.size(), -1);

    int d = 0;
    while (!q.empty()) {
        int v = q.front();
        d = qd.front();
        qd.pop();
        q.pop();
        if (v == end) {
            break;
        }
        for (int i = 0; i < graph[v].size(); i++) {
            int u = graph[v][i];
            if (visited[u] == false) {
                q.push(u);
                parent[u] = v;
                visited[u] = true;
                qd.push(d+1);
            }
        }
    }

    // print path (reversed)
    while (end != -1) {
        printf("%d ", end);
        end = parent[end];
    }
    printf("\n");
    return d;
}

int main() {
    std::vector<std::vector<int>> graph(4);
    graph[0].push_back(1);
    graph[1].push_back(0);
    graph[1].push_back(2);
    graph[2].push_back(1);
    graph[2].push_back(3);
    graph[3].push_back(2);
    printf("%d\n", bfs(0, 3, graph));
    return 0;
}
