//
//  main.cpp
//  ?
//
//  Created by FB on 7/01/19.
//  Permutations by STL vs standard backtracking
//

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>

int total = 0;

void generate_numbers(int pos, int *a, int n, int *sel, int m) {
    if (pos == n) {
        total++;
        /*
         for (int i = 0; i < n; i++) {
         printf("%d\t", a[i]);
         }
         printf("\n");
         */
    }
    for (int j = 0; j < m; j++) {
        if (!sel[j]) { // not selected yet
            a[pos] = j;
            sel[j] = 1;
            generate_numbers(pos+1, a, n, sel, m);
            sel[j] = 0;
        }
    }
}

int main(int argc, const char * argv[]) {
    clock_t begin, end;
    double time_spent;
    begin = clock();
    //freopen("in.txt" , "r" , stdin);

    int a[10] = {0};
    int sel[10] = {0};
    generate_numbers(0, a, 10, sel, 10);
    printf("%d\n", total);
    // 10! = 3,628,800 // 0.24


    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent); // 0.246944

    // vs stl 0.348898
    begin = clock();
    total = 0;
    std::vector<int> s;
    for (int i = 0; i < 10; i++) {
        s.push_back(i);
    }
    do {
        total++;
    } while (next_permutation(s.begin(), s.end()));
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);

    return 0;
}
