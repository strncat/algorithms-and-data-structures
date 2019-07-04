//
//  Backtracking: generate all permutations
//  Source: Algorithms Design Manual / Programming Challenges
//
/*
   a[k=1, k=2, ...        k=n]
   for each position k we generate a set of possible candidates 
   and then for each of these choices we repeat the process for
   position k+1 recursively

     k = 0
    /     |     \
    1     2      3    k = 1
   / \   / \    / \
  2   3  1  3  1   2   k = 2
  |   |  |  |  |   |
  3   2  3  1  2   1   k = 3
*/

#include <iostream>
#include <vector>

#define NMAX 10
#define CMAX 3

int is_a_solution(int *a, int k, int n) {
    return (k == n);
}

// This function fills an array c with possible candidates for the kth position
// of a, given the contents of the first k - 1 positions
void construct_candidate(int *a, int k, int n, int *c, int *ncandidates) {
    int permutation[NMAX] = {false};
    for (int i = 1; i < k; i++) {
        permutation[a[i]] = true;
    }

    for (int i = 1; i <= n; i++) {
        if (permutation[i] == false) {
            c[(*ncandidates)++] = i;
        }
    }
}

void process_solution(int *a, int k) { // just print the solution
    for (int i = 1; i <= k; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void backtrack(int *a, int k, int size) {
    if (is_a_solution(a, k, size)) { // could be just if (n == k) print solution
        process_solution(a, k);
        return;
    }
    int c[CMAX]; // candidates for the next position
    int ncandidates = 0;
    k = k + 1;
    construct_candidate(a, k, size, c, &ncandidates);

    // try all possibilities for the kth position and recurse
    for (int i = 0; i < ncandidates; i++) {
        a[k] = c[i];
        backtrack(a, k, size);
    }
}

void generate_solution(int n) {
    int a[NMAX];
    backtrack(a, 0, n);
}

int main() {
    generate_solution(3);
    return 0;
}
