//
//  Integer Partition without Rearrangement
//  Brute Force, Backtracking solution
//  Given a and k, partition a into k elements without rearrangement
//  This is will just enumerate all possible partitions
//
//  Created by FB on 3/24/17.
//  Copyright © 2017 FB. All rights reserved.
//

#include <iostream>
#include <vector>

using std::vector;

vector<vector<int>> parititions;

void integer_parition(vector<int>& a, int start, int index,
                      int k, vector<vector<int>> parititions) {
    if (parititions.size() == k && start >= a.size()) {
        // we're done
        int max_sum = 0;
        for (int i = 0; i < parititions.size(); i++) {
            int sum = 0;
            for (int j = 0; j < parititions[i].size(); j++) {
                printf("%d ", parititions[i][j]);
                sum += parititions[i][j];
            }
            if (sum > max_sum) { max_sum = sum; }
            printf("\n");
        }
        printf("---\n");
        return;
    }
    if (index >= a.size()) { return; }

    // (1) either continue without placing a divider
    integer_parition(a, start, index+1, k, parititions);


    // (2) or place the divider here
    vector<int> p;
    for (int i = start; i <= index; i++) {
        p.push_back(a[i]);
    }
    parititions.push_back(p);
    integer_parition(a, index+1, index+1, k, parititions);
}

int main() {
    vector<int> a = {1,2,3,4,5,6,7,8,9};
    vector<vector<int>> partitions;
    integer_parition(a, 0, 0, 3, partitions);
    return 0;
}
