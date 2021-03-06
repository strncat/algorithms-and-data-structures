//
//
//  Dynamic Programming: Knapsack
//  0/1 Knapsack, we have at most 1 copy of each item {w_i, v_i}
//  We have a collection of n items, each has a weight w_i and a value v_i
//  Let K[W, n] be the maximum total value we can achieve (subject to the constraint <= W)
//  K[w, n] = max { K[W, n - 1], K[W - wn][n - 1] + cn }
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

int knapsack_01(std::vector<item> &bag, int W) {
    int K[100][100] = {0};

    // base case k[0][j] = 0, K[i][0] = 0
    for (int w = 1; w <= W; w++) { // for each weight w
        for (int i = 1; i <= bag.size(); i++) { // for each item i:

            // case 1: item i is not in the optimal solution
            K[w][i] = K[w][i-1];

            // case 2: item i is in the optimal solution
            if (bag[i-1].w <= w && bag[i-1].v + K[w - bag[i-1].w][i-1] > K[w][i]) {
                K[w][i] = bag[i-1].v + K[w - bag[i-1].w][i-1];
            }
        }
    }

    // print items
    int res = K[W][bag.size()];
    printf("%d\n", res);

    int cur_w = W;
    int cur_v = K[W][bag.size()];
    for (int i = (int)bag.size(); i > 0 && res > 0; i--) {
        if (cur_v != K[cur_w][i-1]) {
            printf("%d %d\n", bag[i-1].w, bag[i-1].v);
            cur_v -= bag[i-1].v;
            cur_w -= bag[i-1].w;
        }
    }

    printf("\n");
    printf("Optimal value = %d\n", K[W][bag.size()]);
    return K[W][bag.size()];
}

int main(int argc, const char * argv[]) {
    std::vector<item> bag;
    bag.push_back(item(2,4)); // taco
    bag.push_back(item(6,17)); // burrito
    bag.push_back(item(7,6));
    bag.push_back(item(1,3));

    // 0/1 Knapsack
    knapsack_01(bag, 13);
    return 0;
}
