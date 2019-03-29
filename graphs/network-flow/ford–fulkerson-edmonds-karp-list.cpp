//
//  main.cpp
//  uhunt
//  Ford–Fulkerson Edmonds-Karp
//  Based on the Algorithms Design Manual
//  Example Problem: https://uva.onlinejudge.org/external/8/820.pdf
//  2017/03/09
//
//
//  In this implementation I don't handle multiple edges between two vertices
//  I do handle the multiple edges case in the adjacency matrix implementation
//  I need to review this, although works, so much not needed stuff

#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::pair;

/* For each edge (i,j) in G with capacity c(i,j) and flow f(i,j), R(G,f) may contain two edges:
 (i) an edge (i,j) with weight c(i,j) − f(i,j), if c(i,j) − f(i,j) > 0 and
 (ii) an edge (j,i) with weight f(i,j), if f(i,j) > 0.
 */

class edge {
public:
    int y;
    int capacity;
    int residual;
    edge(int u, int c) {
        y = u;
        capacity = c;
        residual = c; // c - f
    }
};

bool bfs(vector<vector<edge>>& g, int start, int end, vector<int>& parent) {
    std::queue<int> q;
    vector<bool> visited;

    for (int i = 0; i < g.size(); i++) {
        visited.push_back(false);
        parent.push_back(-1);
    }
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        if (v == end) {
            return true;
        }

        for (int i = 0; i < g[v].size(); i++) {
            edge u = g[v][i];
            if (u.residual > 0 && visited[u.y] == false) {
                q.push(u.y);
                visited[u.y] = true;
                parent[u.y] = v;
            }
        }
    }
    return false;
}

void add_residual_edges(vector<vector<edge>>& g) {
    vector<vector<edge>> t;
    for (int i = 0; i < g.size(); i++) {
        t.push_back(vector<edge>());
    }
    // add backward edges with 0 residual capacity to a temp graph
    for (int i = 0; i < g.size(); i++) {
        for (int j = 0; j < g[i].size(); j++) {
            t[g[i][j].y].push_back(edge(i, 0));
        }
    }
    // add all to g
    for (int i = 0; i < t.size(); i++) {
        for (int j = 0; j < t[i].size(); j++) {
            g[i].push_back(t[i][j]);
        }
    }
}

// find the index of u in v's edges vector
int find_edge(vector<vector<edge>>& g, int v, int u) {
    int index = 0;
    for (; index < g[v].size(); index++) {
        if (g[v][index].y == u) {
            break;
        }
    }
    return index;
}

int find_volume(vector<vector<edge>>& g, vector<int>& parent, int start, int end) {
    int volume = 2 << 27;
    while (parent[end] != -1) {
        int u = parent[end];
        int v = end;

        int index = find_edge(g, u, v); // find u's location in v's edges

        if (g[u][index].residual < volume) {
            volume = g[u][index].residual;
        }
        end = parent[end];
    }
    return volume;
}

void augment(vector<vector<edge>> &g, vector<int>& parent, int start, int end, int volume) {
    while (parent[end] != -1) {
        int u = parent[end];
        int v = end;

        // reduce the residual capacity of edge (i,j)
        int index = find_edge(g, u, v); // find u's location in v's edges
        g[u][index].residual -= volume;

        // but increase the residual capacity of edge (j,i)
        index = find_edge(g, v, u); // find v's location in u's edges
        g[v][index].residual += volume;

        end = parent[end];
    }
}

int netflow(vector<vector<edge>>& g, int source, int sink) {
    // add backward edges for so that we can decrease the flow if we need to
    add_residual_edges(g);

    int volume = 0, sum = 0;
    vector<pair<int,int>> path;
    vector<int> parent;

    while (1) {
        // (1) Edmonds-Karp uses bfs to select the next shortest path
        parent.clear();
        bool ok = bfs(g, source, sink, parent);
        if (!ok) { break; }

        // (2) calculate the volume
        volume = find_volume(g, parent, source, sink);
        sum += volume;

        // (3) last step, augment the path with the new volume
        augment(g, parent, source, sink, volume);
    }
    return sum;
}

int main() {
    /* answer = 25
     4
     1 4 5
     1 2 20
     1 3 10
     2 3 5
     2 4 10
     3 4 20
     0
     */
    freopen("sample.in", "r", stdin);
    int n, network = 1;

    while (scanf("%d", &n) == 1 && n != 0) {

        int s, t, connections;
        scanf("%d %d %d", &s, &t, &connections);

        vector<vector<edge>> graph;
        for (int i = 0; i < n; i++) {
            graph.push_back(vector<edge>());
        }

        int u, v, capacity;
        for (int i = 0; i < connections; i++) {
            scanf("%d %d %d", &u, &v, &capacity);
            graph[u-1].push_back(edge(v-1, capacity));
        }

        int bandwidth = netflow(graph, s-1, t-1);
        
        printf("Network %d\n", network++);
        printf("The bandwidth is %d.\n", bandwidth);
    }
    return 0;
}
