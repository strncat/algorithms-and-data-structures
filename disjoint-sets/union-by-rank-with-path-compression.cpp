//
//  Union By Rank with Path Compression
//  Reference: Algorithms, Stanford - Coursera
//
//  fantastic improvement
//  O(log*n) => log* is the number of times you need to apply log until the result is <= 1
//  every time we perform find, why not just set the
//  parent of every node on the route to the root directly?

#include <iostream>

class UnionByRank {
public:
    int *leader;
    int *rank;
    int n;
    int count;

    UnionByRank(int n) {
        this->n = n;
        count = n; // initially the number of components is n
        leader = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            leader[i] = i; // each item is in its own component
            rank[i] = 0;
        }
    }

    int findOP(int x) { // O(log*(n))
        while (leader[x] != x) { // go up the tree
            leader[x] = leader[leader[x]]; // path compression
            x = leader[x];
        }
        return x;
    }

    int connected(int x, int y) {
        return findOP(x) == findOP(y);
    }

    void unionOP(int x, int y) { // O(log*(n)) Refer to the Rank Lemma Video :)
        int rootX = findOP(x);
        int rootY = findOP(y);
        if (rootX == rootY) return;

        // both have the same size, you're putting one under the other so the rank goes up by one
        if (rank[rootX] == rank[rootY]) {
            leader[rootX] = rootY;
            rank[rootY]++;
        }
        else if (rank[rootX] < rank[rootY]) { // otherwise rank doesn't change
            leader[rootX] = rootY;
        }
        else {
            leader[rootY] = rootX;
        }
        count--;
    }

    void print() {
        printf("number of components %d\n", count);
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
    UnionByRank u(10);

    // going through the connections and checking if they can be merged
    for (int i = 0; i < 11; i++) {
        u.unionOP(connections[i][0], connections[i][1]);
    }
    
    u.print();
    return 0;
}
