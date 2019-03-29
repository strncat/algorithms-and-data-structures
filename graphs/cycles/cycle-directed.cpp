//
//  detect a cycle in a directed graph
//  just use a dfs with maintaining an extra stack/array to keep track of nodes
//

#include <iostream>
#include <vector>

using std::vector;
using std::pair;

bool dfs(int i, vector<vector<int>> &adj, vector<bool> &visited, vector<bool> &stack) {
    visited[i] = true; // mark visited
    stack[i] = true; // put node on stack

    for (int j = 0; j < adj[i].size(); j++) {
        if (stack[adj[i][j]]) {
            return true; // cycle
        }
        if (!visited[adj[i][j]]) {
            bool cycle = dfs(adj[i][j], adj, visited, stack);
            if (cycle) { return true; }
        }
    }

    stack[i] = false; // remove node from stack
    return false;
}

int acyclic(vector<vector<int> > &adj) {
    vector<bool> visited;
    vector<bool> stack;
    for (int i = 0; i < adj.size(); i++) {
        visited.push_back(false);
        stack.push_back(false); // current stack/path we're taking
    }

    for (int i = 0; i < adj.size(); i++) {
        bool cycle = dfs(i, adj, visited, stack);
        if (cycle) { return 1; }
    }
    return 0;
}

int main() {
    //freopen("2.in", "r", stdin);

    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    std::cout << acyclic(adj);
    return 0;
}
