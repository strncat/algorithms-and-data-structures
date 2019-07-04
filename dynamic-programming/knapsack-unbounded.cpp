//
//
//  Dynamic Programming: Knapsack
//  Ubounded Knapsack, we have unlimited copies of each item {w_i, v_i}
//  We have a collection of n items, each has a weight w_i and a value v_i
//  Let K[W, n] be the maximum total value we can achieve (subject to the constraint <= W)
//  K[w] = max_i { K[w-w_i]+v_i }
//
//

#include <iostream>
#include <vector>

typedef struct item {
    int w;
    int v;
    item(int weight, int value) {
        w = weight;
        v = value;
    }
} item;

int unbounded_knapsack(std::vector<item> &bag, int W) {
    std::vector<std::vector<int>> items;
    std::vector<int> K;
    for (int i = 0; i <= W; i++) {
        K.push_back(0);
        items.push_back(std::vector<int>());
    }

    // base case, k[0] = 0
    for (int w = 1; w <= W; w++) { // for each weight w
        for (int i = 0; i < bag.size(); i++) { // for each item i
            if (bag[i].w <= w && bag[i].v + K[w - bag[i].w] > K[w]) {
                // maybe there is a more effient way?
                items[w].clear();
                items[w].push_back(i);
                items[w].insert(items[w].end(), items[w-bag[i].w].begin(), items[w-bag[i].w].end());
                K[w] = bag[i].v + K[w - bag[i].w];
            }
        }
    }

    // print items
    for (int i = 0; i < items[W].size(); i++) {
        printf("(%d %d) ", bag[items[W][i]].w, bag[items[W][i]].v);
    }
    printf("\n");
    printf("Optimal value = %d\n", K[W]);
    return K[W];
}

int main(int argc, const char * argv[]) {
    // Unbounded Knapsack
    std::vector<item> bag;
    bag.push_back(item(2,4)); // taco
    bag.push_back(item(6,17)); // burrito
    unbounded_knapsack(bag, 14);
    return 0;
}
