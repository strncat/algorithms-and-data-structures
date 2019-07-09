//
//  main.cpp
//  tries
//
//  Created by FB on 7/8/19.
//  Copyright © 2019 FB. All rights reserved.
//

#include <iostream>

#define SIZE 26

typedef struct node {
    int value;
    struct node *children[SIZE] = {NULL}; // 26 links / children
} node;

typedef struct trie {
    node *root;
    int count;
    trie() {
        root = new node();
    }

    int search(std::string word) { // O(m) where m is the length of key
        long m = word.length();
        node *current = root;
        for (int i = 0; i < m; i++) {
            int index = word[i] - 'a';
            if (!current->children[index]) { // null pointer
                return 0; // not found
            }
            // move to the child
            current = current->children[index];
        }
        return (current != NULL && current->value);
    }

    void insert(std::string word) {
        if (search(word)) { // word exists
            return;
        }

        int length = (int) word.length();
        node *current = root;

        this->count++; // increment word count

        for (int i = 0; i < length; i++) {
            int index = word[i] - 'a';
            if (!current->children[index]) {
                 // this letter doesn't exist, create it
                current->children[index] = new node();
            }
            // this letter has a link already, follow it along
            current = current->children[index];
        }
        // mark the last node, this is the end of our word
        // this is a marker of an end to a valid word
        current->value = this->count;
    }
} trie;


int main() {
    trie t;
    t.insert("cake");
    t.insert("cakes");
    t.insert("cider");
    t.insert("civil");
    t.insert("cat");
    printf("searching for cat %d\n", t.search("cat"));
    printf("searching for cake %d\n", t.search("cake"));
    printf("searching for ca %d\n", t.search("ca"));
    t.insert("ca");
    printf("searching for ca %d\n", t.search("ca"));
    return 0;
}
