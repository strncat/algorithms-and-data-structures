//
//  main.cpp
//  cartersian trees based on slides from http://web.stanford.edu/class/cs166/
//
//  Created by FB on 4/9/19.
//  Copyright © 2019 FB. All rights reserved.
//

#include <iostream>
#include <stack>
#include <limits.h>

typedef struct ctree {
    struct ctree *left;
    struct ctree *right;
    int key;
} ctree;

void in_order_traversal(ctree *t) {
    if (t == NULL) { return; }
    in_order_traversal(t->left);
    printf("%d ", t->key);
    in_order_traversal(t->right);
}

ctree* cartersian_tree(int *a, int n) {
    std::stack<ctree*> s;
    ctree *root = NULL;
    int min = INT_MAX;

    for (int i = 0; i < n; i++) {
        // (1) create a new node
        ctree *new_node = new ctree;
        new_node->key = a[i];
        new_node->left = NULL;
        new_node->right = NULL;

        // keep track of min as well, to identify the root and return it
        if (min > a[i]) {
            min = a[i];
            root = new_node;
        }

        ctree *last_popped = NULL;
        while (!s.empty() && s.top()->key > a[i]) {
            last_popped = s.top();
            s.pop();
        }
        // (1) the last thing we popped is the new_node's left child
        if (last_popped != NULL) {
            new_node->left = last_popped;
        }

        // (2) whatever is left on the stack is the parent of the new node
        if (!s.empty()) {
            s.top()->right = new_node;
        }
        s.push(new_node);
    }

    return root;
}

int main(int argc, const char * argv[]) {
    int a[6] = {32, 45, 16, 18, 9, 33};
    ctree* root = cartersian_tree(a, 6);
    in_order_traversal(root);
    return 0;
}
