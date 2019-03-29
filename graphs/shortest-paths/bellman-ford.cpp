//
//  bellman-ford
//

#include <iostream>
#include <vector>

typedef std::vector<std::vector<std::pair<int,int>>> graph;

void print(int *distance, long n) {
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; i++) {
        printf("%d \t\t %d\n", i, distance[i]);
    }
}

void BellmanFord(graph& g) {
    int distance[g.size()], parent[g.size()];
    for (int i = 0; i < g.size(); i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }
    distance[0] = 0; // source is node 1

    // Bellman-Ford Dynamic Programming Recurrence
    // let L(i,v) the minimum length of an s-v path
    // L(i,v) = min {L(i-1,v), min over all u-w paths {L(i-1,v) + weight of v-w}}

    for (int s = 1; s <= g.size() - 1; s++) { // for every possible path size

        // for every edge in the graph // double loop
        for (int i = 0; i < g.size(); i++) {
            for (auto e = g[i].begin(); e != g[i].end(); e++) {
                int y = e->first;
                int weight = e->second;

                // Recurrence
                if (distance[i] != INT_MAX && distance[i] + weight < distance[y]) {
                    distance[y] = distance[i] + weight;
                }
            }
        }
    }

    // check for cycles!
    for (int i = 0; i < g.size(); i++) { // for every edge in the graph
        for (auto e = g[i].begin(); e != g[i].end(); e++) {
            int y = e->first;
            int weight = e->second;
            if (distance[i] != INT_MAX && distance[i] + weight < distance[y]) {
                printf("negative weight cycle\n");
            }
        }
    }
    print(distance, g.size());
}

int main() {
    graph g;

    for (int i = 0; i < 5; i++) {
        g.push_back(std::vector<std::pair<int,int>>());
    }

    g[0].push_back(std::pair<int,int>(1,-1));
    g[0].push_back(std::pair<int,int>(2, 4));
    g[1].push_back(std::pair<int,int>(2, 3));
    g[1].push_back(std::pair<int,int>(3, 2));
    g[3].push_back(std::pair<int,int>(1, 1));
    g[1].push_back(std::pair<int,int>(4, 2));
    g[4].push_back(std::pair<int,int>(3, -3));

    BellmanFord(g);
    // correct output
    /*
     Vertex   Distance from Source
     0                0
     1                -1
     2                2
     3                -2
     4                1
     */
    return 0;
}

