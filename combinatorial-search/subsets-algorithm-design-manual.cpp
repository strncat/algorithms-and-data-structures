//
//  Backtracking: generate all subsets of size 2^n
//  Source: Algorithms Design Manual / Programming Challenges
//
//
/*
     k = 0
    /     \
    t      f  k = 1
   / \    / \
  t   f   t   f k = 2
 /\   /\  /\  /\
t f  t f t f  t f  k = 3
 
 for each position in array a, generate the possible candidates:
 for the subsets problem, we either include the element (true) or not (false)
 for each choice {true, false} move onto the next position
*/


#include <iostream>
#include <vector>

#define NMAX 10
#define CMAX 3
bool finished = false;

// tests whether the first k elements of the vector a form a complete solution
int is_a_solution(int *a, int k, int n) {
    return (k == n);
}

// This function fills an array c with the complete set of possible candidates
// for the kth position of a, given the contents of the first k - 1 positions
// for this specific problem, we obviously don't need *a and k
void construct_candidate(int *a, int k, int n, int *c, int *ncandidates) {
    c[0] = true;
    c[1] = false;
    *ncandidates = 2;
}

void process_solution(int *a, int k) { // just print the solution
    printf("{");
    for (int i = 1; i <= k; i++) {
        if (a[i] == true) {
            printf(" %d", i);
        }
    }
    printf(" }\n");
}

void backtrack(int *a, int k, int size) {
    int c[CMAX]; // candidates for the next position
    int ncandidates = 0; // next position candidate count

    if (is_a_solution(a, k, size)) { // could be just if (n == k) print solution
        process_solution(a, k);
    } else {
        k = k + 1; // possibilities for the kth position are:
        construct_candidate(a, k, size, c, &ncandidates);

        // try all possibilities for the kth position and continue
        for (int i = 0; i < ncandidates; i++) {
            a[k] = c[i];
            backtrack(a, k, size);
            if (finished) { // in case we are just looking for one solution, we can terminate early
                return;
            }
        }
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
