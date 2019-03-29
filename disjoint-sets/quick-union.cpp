//
//  Quick-Union (Find in O(n), Union in O(n))
//  Source: https://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf
//
// same as quick-find we start with each element in its own set/component
// In Quick-Find, when we unite, we update all the elements from the first set and the second set
// to have the same leader. In Quick-Union, we don't, we instead use a lazy approach
// where we only unify the leaders of the two elements in question, but because we're not
 //updating the rest of the elements in the set, find will cost O(n) time and
// also affect the union the operation since we anyway need to find the leaders of the two elements

#include <iostream>

class QuickUnion {
public:
    int *leader;
    int n;
    int count;

    QuickUnion(int n) {
        this->n = n;
        count = n; // initially the number of components is n
        leader = new int[n];
        for (int i = 0; i < n; i++) {
            leader[i] = i; // each item is in its own component
        }
    }

    int findOP(int x) { // O(n)
        while (x != leader[x]) { // go up the tree
            x = leader[x];
        }
        return x;
    }

    int connected(int x, int y) {
        return findOP(x) == findOP(y);
    }

    void unionOP(int x, int y) { // O(n) because of the find operation
        int i = findOP(x);
        int j = findOP(y);
        if (i == j) { return; }
        leader[i] = j;
        count--;
    }

    void print() {
        printf("number of components = %d\n", count);
        for (int i = 0; i < n; i++) {
            printf("%d %d\n", i, findOP(i));
        }
    }
};

int main() {
    // example, 11 connections between 10 vertices, find the connected components
    int connections[11][2] = { {4, 3}, {3, 8}, {6, 5}, {9, 4}, {2, 1},
        {8, 9}, {5, 0}, {7, 2}, {6, 1}, {1, 0}, {6, 7}};

    // initialize
    QuickUnion u(10);

    // going through the connections and checking if they can be merged
    for (int i = 0; i < 11; i++) {
        u.unionOP(connections[i][0], connections[i][1]);
    }

    u.print();
    return 0;
}
