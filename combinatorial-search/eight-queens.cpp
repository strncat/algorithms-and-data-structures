//
//  Eight Queens
//
//  Created by FB on 9/22/17.
//  Copyright © 2017 FB. All rights reserved.
//


#include <iostream>
#include <math.h>

#define N 8

bool valid_placement(int *q, int queen_index, int potenial_row) {
    for (int i = 0; i < queen_index; i++) {
        // not a horizontal threat
        if (potenial_row == q[i]) {
            return false;
        }
        // not a diagonal threat
        if (abs(q[i]-potenial_row) == abs(i - queen_index)) {
            return false;
        }
    }
    return true;
}

int solve(int *q, int queen_index) {
    if (queen_index == N) {
        return 1;
    }
    int solutions = 0;
    for (int row = 0; row < N; row++) { // we try to place the queen at index in every possible row
        if (valid_placement(q, queen_index, row)) {
            q[queen_index] = row;
            solutions += solve(q, queen_index+1); // we then attempt to place the next queen
            // we don't really need to undo since we're working on the same queen_index ... and next iteration it will get replaced if any
        }
    }
    return solutions;
}


int eiqht_queens() {
    int q[N];
    for (int i = 0; i < N; i++) {
        q[i] = -1;
    }
    return solve(q, 0);
}

int main() {
    int total = eiqht_queens();
    printf("Case 1: %d\n", total);
    return 0;
}
