//
//  Topological Sort
//  Reference; Both the Algorithm Design Manual and CLR
//
//  Created by FB on 7/11/19.
//  Copyright © 2019 FB. All rights reserved.
//

#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <unordered_map>

#define MAX 1000

typedef std::vector<std::vector<int>> graph;
std::unordered_map<int,std::string> m;

void dfs(graph& g, int v, bool *visited, std::stack<int> &ordered) {
    visited[v] = true;
    for (auto i = 0; i < g[v].size(); i++) {
        int u = g[v][i];
        if (visited[u] == false) {
            visited[u] = true;
            dfs(g, u, visited, ordered);
        }
    }
    ordered.push(v); // node is done, we can push it on the ordered stack
}

void topological_sort(graph& g) {
    std::stack<int> ordered;
    bool visited[MAX] = {false};
    // perform dfs until there are no more unvisited nodes
    for(int i = 0; i < g.size(); i++) {
        if (!visited[i]) {
            dfs(g, i, visited, ordered);
        }
    }

    while (!ordered.empty()) {
        //printf("%s\n", m[ordered.top()].c_str());
        printf("%d\n", ordered.top());
        ordered.pop();
    }
}

int main(int argc, const char * argv[]) {
    m[0] = "tar";
    m[1] = "coreutils";
    m[2] = "libbz2";
    m[3] = "libselinux1";
    m[4] = "dpkg";
    m[5] = "multiarch-support";
    graph g;
    for (int i = 0; i < 6; i++) {
        g.push_back(std::vector<int>());
    }
 //   g[1].push_back(2); // coreutils -> libbz2
 //   g[1].push_back(3); // coreutils -> libselinux1
 //   g[2].push_back(3); // libbz2 -> libselinux1
 //   g[3].push_back(5); // ibselinux1 -> multiarch-support
 //   g[4].push_back(0); // dpkg -> tar
 //   g[4].push_back(1); // dpkg -> coreutils
 //   g[4].push_back(2); // dpkg -> libbz2
 //   g[4].push_back(5); // dpkg -> multiarch-support

    g[0].push_back(1);
    g[2].push_back(1);
    g[1].push_back(4);
    g[4].push_back(3);
    g[5].push_back(4);
    g[1].push_back(5);
    g[2].push_back(4);


    topological_sort(g);
    return 0;
}
