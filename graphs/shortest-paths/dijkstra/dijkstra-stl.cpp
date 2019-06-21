//
// Implementation of Dijkstra using std::priority_queue
// Practice Problem: https://www.hackerrank.com/challenges/dijkstrashortreach
//
// 2019/06/20

#include <iostream>
#include <queue>
#include <vector>
#include <limits.h>
#include <algorithm>

#define INF 100000
#define MAX 3004

std::vector<std::vector<std::pair<int,int>>> g;

void dijkstra(int s) {
    std::priority_queue<std::pair<int,int>,
    std::vector<std::pair<int,int>>,
    std::greater<std::pair<int,int>>> q; // min priority queue

    // init distances to INF or INT_MAX for now
    std::vector<int> distance(g.size(), INF);
    std::vector<bool> visited(g.size(), false);

    q.push(std::make_pair(0, s));
    distance[s] = 0;

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        // In Dijkstra, we visit each node once
        // but priority_queue doesn't support a decrease key
        // operation, so we use a visited array

        if (visited[u]) { continue; }
        visited[u] = true;

        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i].first;
            int weight = g[u][i].second;
            if (distance[v] > distance[u] + weight) {
                distance[v] = distance[u] + weight;
                q.push({distance[v], v});
            }
        }
    }

    for (int i = 0; i < g.size(); i++) {
        if (s != i) {
            if (distance[i] == INF) {
                printf("-1 ");
            } else {
                printf("%d ", distance[i]);
            }
        }
    }
    printf("\n");
}

int main() {
    //freopen("in.txt" , "r" , stdin);
    int n, m, t;
    scanf("%d", &t);
    while (t--) {
        g.clear();

        scanf("%d %d", &n, &m);
        int x, y, weight, start;

        for (int i = 0; i < n; i++) {
            g.push_back(std::vector<std::pair<int,int>>());
        }

        for (int i = 0; i < m; i++) {
            scanf("%d %d %d", &x, &y, &weight);
            x--; y--;
            g[x].push_back({y, weight});
            g[y].push_back({x, weight});
        }
        scanf("%d", &start);
        start--;
        dijkstra(start);
    }
    return 0;
}
