//
//  Longest Increasing Subsequence O(n^2) and O(nlogn)
//  Practice: https://www.hackerrank.com/challenges/longest-increasing-subsequent/problem
//  Description and Proof: https://strncat.github.io
//
//

#include <iostream>

const int MAX = 1000111;
const int INF = 1<<30;

void print(int *a, int *p, int index) {
    if (index == -1) {
        return;
    }
    print(a, p, p[index]);
    printf("%d ", a[index]);
}

int longest_increasing_subsequence(int *a, int n) { // O(n^2)
    int c[n], p[n], max = 0, maxIndex = 0;
    // maximum subsequence ending at a[i] is initialy 1
    for (int i = 0; i < n; i++) {
        c[i] = 1;
        p[i] = -1; // parent array
    }

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (a[i] > a[j] && c[i] < c[j] + 1) { // I can extend the subsequence
                c[i] = c[j] + 1;
                p[i] = j;
            }
        }
        if (c[i] > max) { // maximum subsequence so far
            max = c[i];
            maxIndex = i;
        }
    }
    //print(a, p, maxIndex); // if we need to reconstruct, we can use this
    return max;
}

int longest_increasing_subsequence_fast(int *a, int n) { // O(nlogn)
    int m[MAX];
    m[0] = -INF;
    for (int i = 0; i < n; i++) {
        m[i + 1] = INF;
    }

    int k = 0; // keeps track of the length of the longest increasing subsequence found so far
    for (int i = 0; i < n; i++) {
        // in each iteration either a[i] > a[k] meaning we can extend the subsequence
        if (a[i] > m[k]) {
            m[++k] = a[i];
        } else { // or a[i] < a[k] meaning we can update one of the previous subsequences to a better subsequence ending (for why this works check the link in the header)
            // just a binary search
            int first = 0, last = k;
            while (last > first + 1) {
                int mid = (first + last) / 2;
                if (m[mid] < a[i]) {
                    first = mid;
                } else {
                    last = mid;
                }
            }
            m[last] = a[i];
        }
    }
    return k;
}


int main() {
    clock_t begin, end;
    double time_spent;
    begin = clock();
    int n, a[MAX];
    freopen("in.txt" , "r" , stdin);
    freopen("out.txt" , "w" , stdout);

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    printf("%d\n", longest_increasing_subsequence(a, n));
    printf("%d\n", longest_increasing_subsequence_fast(a, n));
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f", time_spent);
}
