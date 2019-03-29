//
//  heap with objects
//
//  Created by Fatima B on 3/5/16.
//

#include <iostream>
#include <vector>

class Heap {
    std::pair<int,int> array[100];
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
        } else if (array[parent].second > array[child].second) {
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
                if (array[min].second > array[child + i].second) {
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
        std::pair<int,int> minimum_node = array[1];
        array[1] = array[n];
        n--;
        bubble_down(1); // node 1 might not be in its correct position
        printf("minimum node is (%d,%d)\n", minimum_node.first, minimum_node.second);
    }

    void insert(std::pair<int,int> node) {
        n++;
        array[n] = node;
        bubble_up(n); // node n might not be in its correct position
    }


};

int main() {
    Heap h;
    h.insert(std::make_pair(4,5));
    h.insert(std::make_pair(2,3));
    h.extract_min();

    h.insert(std::make_pair(6,0));
    h.insert(std::make_pair(3,-2));
    h.extract_min();

    return 0;
}
