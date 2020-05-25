//
//  In Place Quickselect - CLRS
//
//  Created by FB on 5/23/20.
//  Copyright © 2020 FB. All rights reserved.
//

#include <iostream>
#include <vector>
#include <assert.h>

int randomized_partition(std::vector<int>& a, int first, int last) {
    // (1) We choose a random pivot
    srand(time(NULL));
    int random_pivot = rand() % (last+1-first) + first;

    // (2) We put the pivot element at the end of the array
    std::swap(a[random_pivot], a[last]);

    // (3) our pivot pointer is now pointing at the last element of the array
    int pivot = last;

    int index = first;
    for (int i = first; i < last; i++) {
        if (a[i] < a[pivot]) {
            std::swap(a[i], a[index]);
            index++;
        }
    }
    std::swap(a[pivot], a[index]);
    return index;
}

// k = 1 is the smallest element in a
// k = n is the largest element in a
int quickselect(std::vector<int>& a, int first, int last, int k) {
    // if we only have 3 elements, just sort
    if (last - first < 4) {
        std::partial_sort(a.begin()+first, a.begin()+last, a.end());
        return a[first+k-1];
    }

    // else, partition the array around a random pivot
    int p = randomized_partition(a, first, last);


    int left_length = p - first;

    // we lucked out, we're exactly at the kth element
    // remember that indexing start at 0 and so we want k-1
    // also we return the kth element starting at position first and not 0
    // so we have take that into account when we return the element
    if (k-1 == left_length) {
        return a[first+k-1];
    }

    // otherwise, we either search the left half or the right haf
    if (k-1 < left_length) {
        return quickselect(a, first, p-1, k);
    } else {
        return quickselect(a, p+1, last, k-left_length-1);
    }
}

int main() {
    std::vector<int> a;
    a.push_back(7); a.push_back(6); a.push_back(5); a.push_back(4);
    a.push_back(3); a.push_back(2); a.push_back(1);

    // want 2nd largest or 6-2+1= 5th smallest
    //printf("%d\n", quickselect(a, 0, (int)a.size()-1, 5));

    // second smallest is 2
    int smallest = quickselect(a, 0, (int)a.size()-1, 1);
    assert(smallest == 1);

    int second_smallest = quickselect(a, 0, (int)a.size()-1, 2);
    assert(second_smallest == 2);

    int third_smallest = quickselect(a, 0, (int)a.size()-1, 3);
    assert(third_smallest == 3);

    assert(quickselect(a, 0, (int)a.size()-1, 4) == 4);
    assert(quickselect(a, 0, (int)a.size()-1, 5) == 5);
    assert(quickselect(a, 0, (int)a.size()-1, 6) == 6);
    assert(quickselect(a, 0, (int)a.size()-1, 7) == 7);
    return 0;
}
