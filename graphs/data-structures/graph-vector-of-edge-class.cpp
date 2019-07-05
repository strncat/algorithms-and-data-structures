//
//  Just a graph ... meh
//

#include <iostream>
#include <stack>
#include <vector>

class Edge {
public:
    int y;
    int weight;
    Edge(int y, int weight) {
        this->y = y;
        this->weight = weight;
    }

    Edge(int y) {
        this->y = y;
    }
};

void print(std::vector<std::vector<Edge>>& graph) {
    for (int i = 0; i < graph.size(); i++) {
        printf("%d: ", i);
        for (auto j = graph[i].begin(); j != graph[i].end(); j++) {
            printf("%d (%d), ", j->y, j->weight);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    std::vector<std::vector<Edge>> graph(3); // or list
    graph[0].push_back(Edge(1,4));
    graph[1].push_back(Edge(0,4));
    graph[0].push_back(Edge(3,7));
    graph[2].push_back(Edge(1,2));
    print(graph);
    return 0;
}
