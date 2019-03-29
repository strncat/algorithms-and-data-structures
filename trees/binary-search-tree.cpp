//
//  main.cpp
//  temp
//
//  Based on CLRS Chapter 12 Binary Search Tree
//  Created by Fatima B on 1/31/13
//

#include <iostream>
#include <stdlib.h>

typedef struct tree {
    int data;
    struct tree *parent;
    struct tree *left;
    struct tree *right;
} tree;

tree* search(tree *t, int x) { // O(h)
    if (t == NULL || t->data == x) {
        return t;
    }
    if (x < t->data) {
        return(search(t->left, x));
    } else {
        return(search(t->right, x));
    }
}

tree* searchIterative(tree *t, int x) { // O(h)
    while (t != NULL && t->data != x) {
        if (x < t->data) {
            t = t->left;
        } else {
            t = t->right;
        }
    }
    return t;
}

tree* treeMinimum(tree *t) { // O(h)
    while (t->left) { t = t->left; }
    return t;
}

tree* treeMaximum(tree *t) { // O(h)
    while (t->right) { t = t->right; }
    return t;
}

tree* successor(tree *t) {
    if (t->right != NULL) {
        return treeMinimum(t->right);
    }
    tree *p = t->parent;
    while (p != NULL && p->right == t) { // while t is a right child, continue going up
        t = p;
        p = p->parent;
    }
    return p; // either p is a left child now or just NULL
}

void insert(tree **t, int x, tree *parent) { // O(h)
    tree *child;
    if (*t == NULL) {
        child = (tree*) malloc(sizeof(tree)); // allocate new node
        child->data = x;
        child->left = child -> right = NULL;
        child->parent = parent;
        *t = child;  // link into parent’s record
        return;
    } else if (x < (*t)->data) {
        insert(&((*t)->left), x, *t);
    } else {
        insert(&((*t)->right), x, *t);
    }
}

void insertIterative(tree **l, int x) { // O(h)
    tree *temp = *l;
    tree *child, *parent = NULL;

    while (temp != NULL) { // find the parent of the node
        parent = temp;
        if (x < temp->data) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    child = (tree*) malloc(sizeof(tree)); // allocate new node
    child->data = x;
    child->left = child -> right = NULL;

    child->parent = parent; // update the parent's pointer
    if (parent == NULL) {
        *l = child; // tree is empty, child is the new root
    } else if (child->data < parent->data) {
        parent->left = child;
    } else {
        parent->right = child;
    }
}

// page 296, u's parent will now be v's parent
void transplant(tree **root, tree *u, tree *v) {
    if (u->parent == NULL) {
        *root = v;
    } else if (u == u->parent->left) { // u is a left child
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
}

/* example if we're deleting node z = 8, we find the minimum in the right subtree
 which is y = 9, y of course can't have left children but can possibly have a right child 10
 we first make y->parent = 13 the new parent of 10 after that, we replace z (node 8) with our 10

 6
 /   \
 3     8
 / \   / \
 2  4  7  13
 /
 9
 \
 10
 */

void deleteTree(tree **root, int key) {
    tree *z = search(*root, key);
    if (z == NULL) { return; }

    if (z->left == NULL) { // we replace z by its right child
        transplant(root, z, z->right);

    } else if (z->right == NULL) { // we replace z by its left child
        transplant(root, z, z->left);

    } else {
        tree *y = treeMinimum(z->right); // we find z's successor

        // facts about y
        // y is either z->right itself or is in the left subtree of z->right
        // y can't have a left child, by definition it's the minimum

        if (y->parent != z) { // so y isn't z->right itself
            transplant(root, y, y->right); // y's parent is now y->right's parent
            y->right = z->right; // y will take z's right child
            y->right->parent = y;
        }
        transplant(root, z, y); // z's parent will now be y's parent
        y->left = z->left; // y will take z's left child
        y->left->parent = y;
    }
    free(z);
}

// not CLRS for a recursive method for a tree without parent pointers
// not as good as CLRS!
tree* deleteTreeRecursive(tree *root, int key) {
    if (root == NULL) { return NULL; }
    // locate the node
    if (key < root->data) {
        root->left = deleteTreeRecursive(root->left, key);
    } else if (key > root->data) {
        root->right = deleteTreeRecursive(root->right, key);
    } else { // delete the node
        // node with only one child or no child
        tree *temp;
        if (root->left == NULL) {
            temp = root->right; // right will be a child of the grand parent
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            temp = root->left;
            free(root);
            return temp;
        }
        // two children
        temp = treeMinimum(root->right); // minimum node in the right subtree, successor of root
        root->data = temp->data; // the minimum will repace our node
        root->right = deleteTreeRecursive(root->right, temp->data); // delete the minimum hmm not efficient
    }
    return root;
}

void inOrderTraversal(tree *l) { // O(n)
    if (l) {
        inOrderTraversal(l->left);
        printf("%d ", l->data);
        inOrderTraversal(l->right);
    }
}

void preOrderTraversal(tree *l) { // O(n)
    if (l) {
        printf("%d ", l->data);
        preOrderTraversal(l->left);
        preOrderTraversal(l->right);
    }
}

void postOrderTraversal(tree *l) { // O(n)
    if (l) {
        postOrderTraversal(l->left);
        postOrderTraversal(l->right);
        printf("%d ", l->data);
    }
}

int main() {
    /* example
     15
     /    \
     6      18
     /  \     / \
     3    7   17  20
     / \    \
     2   4   13
     /
     9
     */
    tree *t = NULL;
    insertIterative(&t, 15);
    insertIterative(&t, 6);
    insertIterative(&t, 18);
    insertIterative(&t, 3);
    insertIterative(&t, 7);
    insertIterative(&t, 17);
    insertIterative(&t, 20);
    insertIterative(&t, 2);
    insertIterative(&t, 4);
    insertIterative(&t, 13);
    insertIterative(&t, 9);

    tree *min = treeMinimum(t);
    tree *max = treeMaximum(t);
    printf("Tree Minimum: %d Tree Minimum: %d\n", min->data, max->data);

    printf("In order traversal: "); inOrderTraversal(t); printf("\n");
    printf("Pre traversal: "); preOrderTraversal(t); printf("\n");
    printf("Post traversal: "); postOrderTraversal(t); printf("\n");

    printf("deleting node 9: ");
    deleteTree(&t, 9);
    inOrderTraversal(t);
    printf("\ndeleting node 7: ");
    deleteTree(&t, 7);
    inOrderTraversal(t);
    printf("\ndeleting node 15: ");
    deleteTree(&t, 15);
    inOrderTraversal(t);
    return 0;
}
