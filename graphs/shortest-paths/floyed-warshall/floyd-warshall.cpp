//
//  Floyd Warshall
//  Reference: Stanford Algorithms, Coursera
//

#include <iostream>
#include <limits.h>

#define N 1002
int distance[N][N];

void floyd_warshall(int distance[N][N], int n) { // O(n^3)
    // dynamic programming recurrence:
    // the shortest path between i and j contains some internal nodes (none repeated, simple path)
    // let k be an internal node, either node k is on the optimal path or it's not
    // if k is on the path => the shortest distance is d[i][k] + d[k][j]
    // if k is not on the optimal path => the shortest distance is dij
    // if k is zero, then the shortest distance is just wij (if it exist) otherwise infinity

    for (int k = 1; k <= n; k++) { // number of internal nodes on the path
        for (int i = 1; i <= n; i++) {
             for (int j = 1; j <= n; j++) {
                 if (distance[i][k] == INT_MAX || distance[k][j] == INT_MAX) { continue; }
                 // current distance vs distance though k (from i to k then k to j)
                 distance[i][j] = std::min(distance[i][j], distance[i][k] + distance[k][j]);
            }
        }
    }

    // checking for negative cycles
    for (int i = 1; i <= n; i++) {
        if (distance[i][i] < 0) {
            printf("negative cycle detected\n");
            return; // we should not use the distance matrix if negative cycles were detected
        }
    }
}

int main() {
    freopen("in.txt", "r", stdin); // read test cases
    //freopen("out.txt", "w", stdout);

    int vertices, edges, a, b, weight;
    scanf("%d %d", &vertices, &edges);

    printf("vertices=%d edges=%d\n", vertices, edges);

    // initalize everything to infinity = INT_MAX
    for (int i = 1; i <= vertices; i++) {
        for (int j = 1; j <= vertices; j++) {
            if (i == j) {
                distance[i][j] = 0; // distance from node to itself is zero
            } else {
                distance[i][j] = INT_MAX; // otherwise infinity
            }
        }
    }

    // specific to this assignment
    // this graph might contain more than one edge between two vertices
    for (int i = 0; i < edges; i++) {
        scanf("%d %d %d", &a, &b, &weight);
        if (distance[a][b] > weight) { // pick the shortest edge
            distance[a][b] = weight;
        }
    }
    floyd_warshall(distance, vertices);
    return 0;
}
