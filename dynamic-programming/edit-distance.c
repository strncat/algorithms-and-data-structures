//
// Minimum Edit Distance 2014/8/10
// source: http://www.cs.toronto.edu/~frank/csc401/tutorials/Levenshtein.pdf
//
// Example: the best way to align the following strings is to remove G and insert C in the first string
// G C {G} T A T G [C] C
// G C     T A T G  C  C
//
// The edit distnace algorithm computes minimum number of operations required to transform s1 into s2
// with respect to the first string, we can also use the algorithm to trace back the route
//
// The output for the above example is
// MMDMMMMMIM which matches the correct answer manually computed, delete & insert 
// 2 is the minimum number of operatinos required

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 100

int min(int a, int b) { return a < b ? a : b; }

void reverse(char *s) {
    char *p = s;
    while (*p) { p++; } p--;
    while (s < p) {
        char temp = *s;
        *s = *p;
        *p = temp;
        s++;
        p--;
    }
}

void construct(char path[N][N], int n, int m) { // O(m + n)
    int i = n;
    int j = m;
    char script[N]; // this the sequence of operations that we will perform to transform s1 to s2

    int index = 0;
    while (i >= 0 && j >= 0) {
        if (path[i][j] == '0') /* same letter */ {
            i--;
            j--;
            script[index++] = 'M';
        } else if (path[i][j] == 'd') { /* if we deleted a character we go up in the matrix (row up) */
            i--;
            script[index++] = 'D';
        } else if (path[i][j] == 'i') { /* if we inserted a character we go left (column to the left) */
            j--;
            script[index++] = 'I';
        } else if (path[i][j] == 'r') {
            i--;
            j--;
            script[index++] = 'R';
        }
    }
    script[index] = '\0';
    reverse(script);
    // need to reverse it first, c++ use std::reverse
    printf("%s\n", script);
}

int edit_distance(char *s1, char *s2) { // O(m*n)
    int distance[N][N];
    char path[N][N];
    memset(distance, 0, sizeof(distance));
    memset(path, '0', sizeof(path));
    int n = (int) strlen(s1);
    int m = (int) strlen(s2);

    for (int i = 1; i <= n; i++) { // going right => delete
        distance[i][0] = i;
        path[i][0] = 'd';
    }

    for (int j = 1; j <= m; j++) { // going down => insert
        distance[0][j] = j;
        path[0][j] = 'i';
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int delete = distance[i - 1][j] + 1;
            int insert = distance[i][j - 1] + 1;
            int replace = distance[i - 1][j - 1] + (s1[i] != s2[j]); // replace cost could be anything
            distance[i][j] = min(min(insert, delete), replace);

            if (delete == distance[i][j]) { /* if the minimum came from up, we delete a character */
                path[i][j] = 'd';
            } else if (insert == distance[i][j]) { /* if the minimum came from left we insert a character */
                path[i][j] = 'i';
            } else if (s1[i] != s2[j]) { /* replace */
                path[i][j] = 'r';
            } else {
                path[i][j] = '0'; /* no operation required */
            }
        }
    }
    construct(path, n, m);
    return distance[n][m]; // the number of operations needed (minimum edit distance)
}

int main() {
    char x[] = "GCGTATGC", y[] = "GCTATGCC";
    printf("%d\n", edit_distance(x, y));
    return 0;
}
