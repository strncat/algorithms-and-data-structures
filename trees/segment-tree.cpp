//
//  segment-tree.cpp
//  SegmentTree
//
//  Created by Fatima B on 3/16/15.
//  Copyright (c) 2015 Apple. All rights reserved.
//

#include <stdio.h>
#include <math.h>

class SegmentTree {
public:
    int *buffer; // we will allocate dynamically
    int n;
    SegmentTree(int *a, int n); // create a segment tree for array a
    int FillSegmentTree(int *a, int first, int last, int index);
    int getSum(int lrange, int rrange);
    void updateValue(int a[], int n, int i, int newVal);
    void print();
private:
    int getSumHelper(int first, int last, int lrange, int rrange, int current);
    void updateValueHelper(int first, int last, int i, int diff, int index);
};

void SegmentTree::print() {
    for (int i = 0; i < n; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

SegmentTree::SegmentTree(int *a, int n) {
    int height = (int) (ceil(log2(n))); // Height of segment tree
    int max_size = 2 * (int) pow(2, height) - 1; // Maximum size of segment tree
    buffer = new int[max_size];
    this->n = n;

    // Fill the segment tree with array elements
    FillSegmentTree(a, 0, n-1, 0);
}

int SegmentTree::FillSegmentTree(int *a, int first, int last, int current) {
    if (first == last) { // one element in the array
        buffer[current] = a[first];
        return a[first];
    }

    // If there are more than one element, then the sum stored in the current node
    // = sum return from the left subtree + sum returned from the right subtree

    int mid = first + (last - first) / 2;

    buffer[current] =  FillSegmentTree(a, first, mid, current*2 + 1) +
    FillSegmentTree(a, mid + 1, last, current*2 + 2);

    return buffer[current];
};

int SegmentTree::getSumHelper(int first, int last, int lrange, int rrange, int current) {

    // first and last are the boundaries of the segment tree
    // lrange and rrange are the boundaries of the range
    // current is the current node in the tree, intially it's the root, current = 0

    if (first >= lrange && last <= rrange) { return buffer[current]; }

    // If the segment of this node is outside the given range, return 0
    if (last < lrange || first > rrange) { return 0; }

    // If a part of this segment overlaps with the given range
    int mid = first + (last - first) / 2;

    return getSumHelper(first, mid, lrange, rrange, 2*current + 1) +
    getSumHelper(mid + 1, last, lrange, rrange, 2*current + 2);
}

int SegmentTree::getSum(int lrange, int rrange) {
    if (lrange < 0 || rrange > n - 1 || lrange > rrange) {
        printf("Invalid Input");
        return -1;
    }
    return getSumHelper(0, n - 1, lrange, rrange, 0);
}


void SegmentTree::updateValueHelper(int first, int last, int i, int diff, int index) {
    // Base Case: If the input index lies outside the range of this segment
    if (i < first || i > last)
        return;

    // If the input index is in range of this node, then update the value
    // of the node and its children
    buffer[index] = buffer[index] + diff;
    if (last != first) {
        int mid = first + (last - first) / 2;
        updateValueHelper(first, mid, i, diff, 2*index + 1);
        updateValueHelper(mid+1, last, i, diff, 2*index + 2);
    }
}

// The function to update a value in input array and segment tree

void SegmentTree::updateValue(int a[], int n, int i, int newVal) {

    if (i < 0 || i > n-1) {
        printf("Invalid Input");
        return;
    }

    // Get the difference between new value and old value
    int diff = newVal - a[i];

    // Update the value in array
    a[i] = newVal;

    // Update the values of nodes in segment tree
    updateValueHelper(0, n-1, i, diff, 0);
}
