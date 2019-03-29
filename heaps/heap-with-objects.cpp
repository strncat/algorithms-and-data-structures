//
//  heap with objects
//
//  Created by Fatima B on 3/5/16.
//

#include <iostream>
#include <vector>

typedef struct Node {
    int key;
    int value;
    Node() {
        key = 0;
        value = 0;
    }
    Node(int k, int v) {
        key = k;
        value = v;
    }
} Node;

class Heap {
    Node array[100];
    int n;
public:
    Heap() { n = 0; }

    // useful functions
    bool empty() { return (n == 0); }
    int left_child(int parent) { return (2 * parent); }
    int right_child(int parent) { return (2 * parent) + 1; }
    int get_parent(int child) { if (child == 1) { return -1; } else { return child/2; } }

    // a leaf node that has a value less than its parent needs to go up the tree
    void bubble_up(int child) {
        int parent = get_parent(child);
        if (parent == -1) {
            return;
        } else if (array[parent].value > array[child].value) {
            std::swap(array[child], array[parent]);
            bubble_up(parent);
        }
    }

    // a parent node that is greater than its children needs to go down the tree
    void bubble_down(int parent) {
        int child = left_child(parent);
        int min = parent;

        for (int i = 0; i <= 1; i++) {
            if ((child + i) <= n) {
                if (array[min].value > array[child + i].value) {
                    min = child + i;
                }
            }
        }

        if (min != parent) {
            std::swap(array[min], array[parent]);
            bubble_down(min);
        }
    }

    void extract_min() {
        if (n == 0) { return; } // error
        Node minimum_node = array[1];
        array[1] = array[n];
        n--;
        bubble_down(1); // node 1 might not be in its correct position
        printf("minimum node is (%d,%d)\n", minimum_node.key, minimum_node.value);
    }

    void insert(Node node) {
        n++;
        array[n] = node;
        bubble_up(n); // node n might not be in its correct position
    }
};

int main() {
    Heap h;
    h.insert(Node(4,5));
    h.insert(Node(2,3));
    h.extract_min();

    h.insert(Node(6,0));
    h.insert(Node(3,1));
    h.insert(Node(3,-2));
    h.extract_min();
    return 0;
}
