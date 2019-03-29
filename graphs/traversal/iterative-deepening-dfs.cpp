//
//  Iterative Deeepening Depth First Search
//  Based on geeksforgeeks
//

#include <iostream>
#include <stack>
#include <vector>

using std::vector;

bool dfs_limit(int source, int target, std::vector<vector<int>>& graph, int depth) {
    if (source == target) { return true; }
    if (depth <= 0) { return false; }

    for (int i = 0; i < graph[source].size(); i++) {
        int u = graph[source][i];
        if (dfs_limit(u, target, graph, depth-1)) {
            return true;
        }
    }
    return false;
}

bool iddfs(int source, int target, std::vector<vector<int>>& graph, int max_depth) {
    for (int i = 0; i <= max_depth; i++) {
        if (dfs_limit(source, target, graph, i)) {
            return true;
        }
    }
    return false;
}

int main() {
    std::vector<vector<int>> graph(7);

    /*
          0
        /   \
       1     2
      / \   / \
     3   4 5   6
    */

    graph[0].push_back(1);
    graph[1].push_back(0);

    graph[0].push_back(2);
    graph[2].push_back(0);

    graph[1].push_back(3);
    graph[3].push_back(1);

    graph[1].push_back(4);
    graph[4].push_back(1);

    graph[2].push_back(5);
    graph[5].push_back(2);

    graph[2].push_back(6);
    graph[6].push_back(2);

    int target = 6, max_depth = 1, source = 0;
    if (iddfs(source, target, graph, max_depth)) {
        printf("Target is reachable\n");
    } else {
        printf("Target is not reachable\n");
    }
    return 0;
}
