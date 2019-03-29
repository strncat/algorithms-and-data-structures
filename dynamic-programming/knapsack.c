//
// Knapsack!
// We have a collection of n items, each has a value/cost ci and a weight wi
// Let K[W, n] be the maximum total value we can achieve (subject to the constraint <= W)
// K[w, n] = either item n is in the optimal solution or it is not
// K[w, n] = max { K[W, n - 1], K[W - wn][n - 1] + cn }
//

#include <stdio.h>

#define N 100
#define maximum(a, b) a > b ? a : b

int knapsack(int W, int n, int *weight, int *cost) {
    int K[N + 1][N + 1];
    for (int i = 0; i <= n; i++) {
        K[i][0] = 0;
    }
    for (int w = 0; w <= W; w++) {
        K[0][w] = 0;
    }
    for (int i = 1; i <= n; i++) { // for each item i
        for (int w = 1; w <= W; w++) { // for each weight w
            if (weight[i - 1] <= w) { // can I carry this item?
                // if I add this item, will my value increase?
                K[i][w] = maximum(cost[i - 1] + K[i - 1][w - weight[i - 1]],  K[i - 1][w]);
            } else {
                // I can't carry this item, move on
                K[i][w] = K[i - 1][w];
            }
        }
    }
    return K[n][W];
}

int knapsackBetter(int W, int n, int *weight, int *cost) { // you really only need two rows at a time
    int K[2][N + 1];
    K[0][0] = 0;
    K[0][1] = 0;
    for (int w = 0; w <= W; w++) {
        K[0][w] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weight[i - 1] <= w) {
                K[i%2][w] = maximum(cost[i - 1] + K[(i - 1)%2][w - weight[i - 1]],  K[(i - 1)%2][w]);
            } else {
                K[i%2][w] = K[(i - 1)%2][w];
            }
        }
    }
    return K[n%2][W];
}

int main() {
    int weight[N];
    int cost[N];
    weight[0] = 1; cost[0] = 1;
    weight[1] = 2; cost[1] = 6;
    weight[2] = 5; cost[2] = 18;
    weight[3] = 6; cost[3] = 22;
    weight[4] = 7; cost[4] = 28;
    int W = 11;
    int n = 5;
    printf("%d\n", knapsackBetter(W, n, weight, cost));
    return 0;
}
