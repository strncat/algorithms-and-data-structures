//
// DFS (Topological Sort)
// Reference: Couresera - Algorithms by Tim Roughgarden
//

#include <iostream>
#include <stack>
#include <vector>

void dfs(std::vector<std::vector<int>>& g, int v,
         bool *visited, int *labels, int *currentLabel) {
    visited[v] = true;
    for (auto i = g[v].begin(); i != g[v].end(); i++) {
        if (visited[*i] == false) {
            visited[*i] = true;
            dfs(g, *i, visited, labels, currentLabel);
        }
    }
    labels[*currentLabel] = v; // labels[v] = *currentLabel;
    (*currentLabel)--;
}


void topological_sort(std::vector<std::vector<int>>& g) {
    int labels[g.size()];
    bool visited[g.size()];
    int currentLabel = (int)g.size()-1; // this is the key to the algorithm

    for(int i = 0; i < g.size(); i++) {
        visited[i] = false;
    }

    for (int i = 0; i < g.size(); i++) {
        if (visited[i] == false) {
            dfs(g, i, visited, labels, &currentLabel);
        }
    }
    // ordered!
    for (int i = 0; i < g.size(); i++) {
        printf("%d ", labels[i]);
    }
    printf("\n");
}

int main() {
    std::vector<std::vector<int>> graph(4);
    graph[0].push_back(2);
    graph[3].push_back(0);
    graph[3].push_back(1);
    graph[3].push_back(2);
    graph[1].push_back(0);

    //correct output is 3 1 0 2
    topological_sort(graph);
    return 0;
}
