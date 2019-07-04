//
//  Find the all the possible pairings of a set
//
//  Number of pairs = n! / (n/2)! 2^(n/2)
//  Example for {1, 2, 3, 4}
//  Possible pairings are (1,2), (3,4) OR (1,3), (2,4) OR (1,4), (2,3)
//
//  Source: http://usaco.org/current/data/sol_wormhole.html
//

#include <iostream>
#include <vector>

#define MAX 12

void pairings(char *elements, int *partner, int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (partner[i] == -1) { // needs a partner
            break;
        }
    }

    if (i == n) { // all paired
        printf("all paired\n");
    }

    // find a possible partner
    for (int j = i + 1; j < n; j++) {
        if (partner[j] == -1) {
            printf("%c %c\n", elements[i], elements[j]);
            partner[i] = j;
            partner[j] = i;
            pairings(elements, partner, n); // continue to find pairs
            // pair i with another element!
            partner[i] = -1;
            partner[j] = -1;
        }
    }
}

int main() {
    int n = 4;
    char elements[MAX] = {'a', 'b', 'c', 'd'};
    int partner[MAX];

    for (int i = 0; i < n; i++) {
        partner[i] = -1;
    }

    pairings(elements, partner, n);
    return 0;
}
