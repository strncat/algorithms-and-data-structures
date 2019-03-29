//
// source: http://www.cs.utexas.edu/users/djimenez/utsa/cs3343/lecture25.html
//
/*
           {1234}
      /      /    \   \
     /      /      \   \
    1       2      3    4  outer loop place 1..n in i=1
 / | \     / \    /
12 13 14  23 24  34        recursive call 
                           first branch: place 2..n in i=2
                           second branch: place 3..n in i=2
*/

#include <stdio.h>
#include <stdlib.h>

void combinations(int *a, int n, int k, int start, int index) {
    if (index > k) { // we are done, print combination
        for (int i = 1; i <= k; i++) {
            printf ("%i ", a[i]);
        }
        printf ("\n");
        return;
    }

    // For each index/position try placing all elements start to n in that index/position
    for (int i = start; i <= n; i++) {
        a[index] = i;
        // now recursively generate combinations for the next position / next possible start
        combinations(a, n, k, i+1, index+1);
    }
}

int main () {
    int a[100], n = 4, k = 3;
    combinations (a, n, k, 1, 1); // n choose k, starting with element 1
    return 0;
}
