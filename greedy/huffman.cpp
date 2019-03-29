//
//  Huffman
//  Reference: Stanford Algorithms - Courersa
//  Minimize L(T) = Sum (pi * depth of i in T) for i in the alphabet
//
//  Use a min heap to store the characters with their frequencies (make a node for each character)
//  pop two elements at a time and make a new node (sum frequences from the two nodes)
//  insert the node back in the heap, continue doing that until you're left with one node
//  this node is your huffman tree root!
//  traverse the tree to generate the codes

#include <iostream>
#include <map>
#include <queue>

typedef struct node {
    int f; // frequency
    char c; // set for leaf nodes
    struct node *left;
    struct node *right;
} node;

struct comparator { // used by the minheap
    bool operator() (node *a, node *b) {
        return a->f > b->f;
    }
};

void generateCodes(node *root, std::map<char, std::string> &m, std::string s) {
    if (root->left == NULL && root->right == NULL) { // leaf node
        m[root->c] = s;
        return;
    }
    // it's an internal node
    generateCodes(root->left, m, s+"0");
    generateCodes(root->right, m, s+"1");
}

node* buildTree(std::map<char, int> &f) {
    std::priority_queue<node*, std::vector<node*>, comparator> minHeap;

    // make a leaf node for each character and add it to the heap
    for (auto t = f.begin(); t != f.end(); t++) {
        node *leaf = new node();
        leaf->c = t->first;
        leaf->f = t->second;
        leaf->left = NULL;
        leaf->right = NULL;
        minHeap.push(leaf);
    }

    // we can handle the case where we have one character only
    // but for now assume we at least have two characters

    // build the tree
    while (minHeap.size() > 1) {

        // extract the the lowest two frequencies
        node *l = minHeap.top();
        minHeap.pop();
        node *r = minHeap.top();
        minHeap.pop();

        // make a node of the two lowest nodes
        node *internal = new node();
        internal->f = l->f + r->f; // sum of the frequencies
        internal->left = l;
        internal->right = r;
        minHeap.push(internal);
    }
    return minHeap.top(); // the root of the tree
}

std::map<char, std::string> constructHuffman(std::map<char, int> &f) {
    node *root = buildTree(f); // build the tree
    std::map<char, std::string> codeMap; // to hold the encodings
    generateCodes(root, codeMap, ""); // fill the map using the tree
    return codeMap;
}

int main() {
    std::map<char, int> frequenices;

    frequenices['A'] = 45; frequenices['B'] = 13; frequenices['C'] = 12;
    frequenices['D'] = 16; frequenices['E'] = 9; frequenices['F'] = 5;

    std::map<char, std::string> m = constructHuffman(frequenices);
    for (auto t = m.begin(); t != m.end(); t++) {
        std::cout << t->first << " " << t->second << std::endl;
    }
    /* a: 0
     b: 101
     c: 100
     d: 111
     e: 1101
     f: 1100
     */
    return 0;
}
