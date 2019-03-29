//
//  Longest Increasing Subsequence O(nlogn)
//  2014
//
/*
 This is different than the O(n^2) algorithm. Here we have an array S where:
 * The index represets the length of the subsequence and
 * S[index] is the last element in that subsequence, "a subsequence of length index ends at element S[index]"

 We loop through the array a and every we have two options
 * The current element a[i] is larger than a[S[len]] meaning that we can extend the sequence
 * We can't extend the sequence, so we need to find the maximum subsequence length ending at our current
 element, we do that by using binary search on S since S is sorted
 */

#include <iostream>

int binary_search(int *s, int *a, int first, int last, int current_element) {
    // find an index such that
    while (first < last) {
        int mid = (first + last) / 2;
        if (a[s[mid]] == current_element) {
            return mid;
        } else if (a[s[mid]] > current_element) {
            last =  mid;
        } else {
            first = mid + 1;
        }
    }
    return first; // worst case: max len is just 1
}

int longest_increasing_sequence(int *a, int *p, int *s, int n) {
    int len = 1; // current length
    s[len] = 0; // s holds the smallest element index that ends an increasing sequence of length i
    // here we're saying if we need a subsequence of length 1, then we can find it at index = 0
    p[0] = -1; // parent array

    for (int i = 1; i < n; i++) {
        // The first part is the typical longest increasing question, if a[i] > a[s[len]] extends the sequence
        if (a[i] > a[s[len]]) {
            p[i] = s[len];
            s[++len] = i;
        }

        // For the current a[i], what is the longest subsequence it can reach?
        // Say it is k, now we need to compare a[i] with a[s[k]]
        // Because if a[i] is smaller, then we should store i in s[k]
        // Since s[k] holds the smallest element that extends a subsequence of length k

        // We usually search all of s to find k but here we use binary search
        // to make it faster given that s is sorted by construction

        else {
            // I want the largest element in s less than a[i]
            int k = binary_search(s, a, 1, len, a[i]);
            if (a[i] < a[s[k]]) { // if truly greater than then replace otherwise no
                s[k] = i;
            }
            p[i] = s[k-1]; // parent of s[k] = i is s[k - 1]
        }
    }
    return len;
}

void construct_subsequence(int *a, int *p, int index) {
    if (p[index] >= 0)
        construct_subsequence(a, p, p[index]);
    printf("%d ", a[index]);
}

int main() {
    int s[16] = {-1}, p[16] = {-1}, a[16] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    int length = longest_increasing_sequence(a, p, s, 16);
    printf("%d\n", length);
    construct_subsequence(a, p, s[length]);
    return 0;
}
