//
//  Quick-Find - (Find in O(1), Union in O(n))
//
// we start with each element in its own set/component
//  each component/set will be represented by an element from the set
//  for example set {1, 2, 3} can be represented by the element = 2 (leader of the set)
//  and set {4, 5, 6} can be represented by element 4 (leader of the set)
//  when we come across the connection (1-6), we pick either 1's leader or 6's leader
//  if we pick 1, all members in the set {4, 5, 6} will have a new leader = 2

// Application: http://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=734


#include <iostream>

class QuickFind {
public:
    int *leader;
    int n;
    int count;

    UnionFind(int n) {
        this->n = n;
        count = n; // initially the number of components is n
        leader = new int[n];
        for (int i = 0; i < n; i++) {
            leader[i] = i; // each item is in its own component
        }
    }

    int findOP(int x) { // constant time to find the leader of x
        return leader[x];
    }

    int connected(int x, int y) {
        return leader[x] == leader[y];
    }

    void QuickFind(int x, int y) { // union takes linear time
        if (connected(x, y)) { return; }
        int l = leader[x];
        for (int i = 0; i < n; i++) { // convert anyone under l to be under leader[y]
            if (leader[i] == l) {
                leader[i] = leader[y];
            }
        }
        count--;
    }

    void print() {
        printf("number of components %d\n", count);
        for (int i = 0; i < n; i++) {
            printf("%d %d\n", i, leader[i]);
        }
    }
};

int main() {
    // example, 11 connections between 10 vertices, find the connected components
    int connections[11][2] = { {4, 3}, {3, 8}, {6, 5}, {9, 4}, {2, 1},
        {8, 9}, {5, 0}, {7, 2}, {6, 1}, {1, 0}, {6, 7}};

    // initialize
    QuickFind uf(10);

    // going through the connections and checking if they can be merged
    for (int i = 0; i < 11; i++) {
        uf.unionOP(connections[i][0], connections[i][1]);
    }

    uf.print();
    return 0;
}
