//
//  Backtracking: Eight Queens
//  Source: Algorithms Design Manual / Programming Challenges
//
/*
   a[k=1, k=2, ...        k=n]
   a is the solution vector, where k is the row and a[k] is the column number
   we generate a set of possible candidates (column numbers) for each row and place them in array c

   To generate candidates for row k we go through possible columns i (1 to 8)
   For each possible position (k,i):
   We have to check if it violates any of the previously placed queens
      - is it a column threat? is i == a[j]?
      - is it a diagonal or cross diagonal threat? abs(a[j]-i) == abs(j-k)?
   If it's not a threat, we add it to array c
*/

#include <iostream>

#define NMAX 10
#define CMAX 10000

int solutions = 0;

int is_a_solution(int *a, int k, int n) {
    return (k == n);
}

void construct_candidate(int *a, int k, int n, int *c, int *ncandidates) {
    // k is the current row number that we're trying to fill
    for (int i = 1; i <= n; i++) { // can we place the queen in column i for row k?
        // check for conflict with previously placed queens
        bool legal_move = true;
        for (int j = 1; j < k; j++) {
            if (a[j] == i) { // column threat
                legal_move = false;
            }
            if (abs(a[j] - i) == abs(j - k)) { // diagonal threat
                legal_move = false;
                break;
            }
        }
        if (legal_move == true) {
            c[(*ncandidates)++] = i; // column i is okay
        }
    }
}

void process_solution(int *a, int k) { // just print the solution
    solutions++;
}

void backtrack(int *a, int k, int size) {
    int c[CMAX]; // candidates for the next position
    int ncandidates = 0; // next position candidate count

    if (is_a_solution(a, k, size)) {
        process_solution(a, k);
    } else {
        k = k + 1;
        // generate possibilities for the kth row
        construct_candidate(a, k, size, c, &ncandidates);

        // try all positions for the kth row and continue
        for (int i = 0; i < ncandidates; i++) {
            a[k] = c[i];
            backtrack(a, k, size);
        }
    }
}

void nqueens(int n) {
    int a[NMAX];
    solutions = 0;
    backtrack(a, 0, n);
    printf("%d\n", solutions);
}

int main() {
    //freopen("sample.in", "r", stdin);
    nqueens(1); // 1
    nqueens(2); // 0
    nqueens(3); // 0
    nqueens(4); // 2
    nqueens(5); // 10
    nqueens(6); // 4
    nqueens(7); // 40
    nqueens(8); // 92
    return 0;
}
