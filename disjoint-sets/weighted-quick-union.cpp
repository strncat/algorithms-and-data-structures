//
//  Weighted-Quick-Union (Find in O(log(n)), Union in O(log(n))
//  Source: https://www.cs.princeton.edu/~rs/AlgsDS07/01UnionFind.pdf
//
// same as quick-union
// in Quick-Union, the cost of find and union was O(n) and that's because the tree can get very deep = O(N)
// to fix that we use weighted-quick-union where make sure the depth of tree doesn't get deep!
// to do that, we create an additional array size to keep track of the size of each component

#include <iostream>

class WeightedQuickUnion {
public:
    int *leader;
    int *size;
    int n;
    int count;

    WeightedQuickUnion(int n) {
        this->n = n;
        count = n; // initially the number of components is n
        leader = new int[n];
        size = new int[n];
        for (int i = 0; i < n; i++) {
            leader[i] = i; // each item is in its own component
            size[i] = 1;
        }
    }

    int findOP(int x) { // O(log(n))
        while (leader[x] != x) { // go up the tree
            x = leader[x];
        }
        return x;
    }

    int connected(int x, int y) {
        return findOP(x) == findOP(y);
    }

    void unionOP(int x, int y) { // O(log(n))
        int rootX = findOP(x);
        int rootY = findOP(y);
        if (rootX == rootY) return;

        // make smaller root point to larger one
        if (size[rootX] < size[rootY]) {
            leader[rootX] = rootY;
            size[rootY] += size[rootX];
        }
        else {
            leader[rootY] = rootX;
            size[rootX] += size[rootY];
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
    freopen("test.txt", "r", stdin);

    bool newline = false;
    int tests;
    std::cin >> tests;

    while (tests--) {
        // new line crap
        if (newline) {
            std::cout << std::endl;
        }
        newline = true;

        // init based on the size of the network
        int n;
        std::cin >> n;
        std::cin.ignore(); // aghhhhh
        WeightedQuickUnion uf(n + 1);

        // connections and questions
        int answered = 0, unanswered = 0;
        for (std::string s; getline(std::cin, s) && !s.empty();) {
            std::stringstream sin(s);
            char c; sin >> c;
            int a, b; sin >> a >> b;
            if (c == 'c') {
                uf.unionOP(a, b); // merge if possible

            } else {
                if (uf.connected(a, b) == true) {
                    answered++;
                } else {
                    unanswered++;
                }
            }
        }
        printf("%d,%d\n", answered, unanswered);
    }
    return 0;
}
