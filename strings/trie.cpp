//
//  main.cpp
//  tries
//
//  Created by FB on 7/8/19.
//  Copyright © 2019 FB. All rights reserved.
//
//  Description: https://strncat.github.io/jekyll/update/2019/07/06/tries.html
//  Practice Problem: https://www.hackerrank.com/challenges/contacts/problem

#include <iostream>
#include <queue>

#define SIZE 26

typedef struct node {
    bool marker;
    int value;
    struct node *children[SIZE] = {NULL}; // 26 links / children
} node;

typedef struct trie {
    node *root;
    trie() {
        root = new node();
    }

    // collect matches recursively from all branches
    // save them in q
    void collect(node *current, std::string prefix,
                 std::queue<std::string> &q) {
        if (current == NULL) { return; }
        if (current->marker) {
            q.push(prefix);
        }
        for (int i = 0; i < SIZE; i++) {
            if (current->children[i] != NULL) {
                char c = i + 'a';
                collect(current->children[i], prefix + c, q);
            }
        }
    }

    // prefix match: print all possible matches
    int words_with_prefix(std::string prefix) {
        node *current = search(prefix);
        if (current == NULL) { return 0; } // no matches
        std::queue<std::string> q;
        collect(current, prefix, q);
        while (!q.empty()) {
            printf("%s\n", q.front().c_str());
            q.pop();
        }
        return current->value; // total matches
    }

    // only return true if it's an exact match
    bool exact_match(std::string word) {
        node *current = search(word);
        return current && current->marker;
    }

    // search for any word/prefix
    node* search(std::string word) {
        long m = word.length();
        node *current = root;
        for (int i = 0; i < m; i++) {
            int index = word[i] - 'a';
            if (!current->children[index]) { // null pointer
                return NULL; // not found
            }
            // move to the child
            current = current->children[index];
        }
        return current;
    }

    void insert(std::string word) {
        if (search(word)) { // word exists
            return;
        }
        int length = (int) word.length();
        node *current = root;
        current->value++; // increment word count

        for (int i = 0; i < length; i++) {
            int index = word[i] - 'a';
            if (!current->children[index]) {
                 // this letter doesn't exist, create it
                current->children[index] = new node();
            }
            // this letter has a link already, follow it along
            current = current->children[index];
            current->value++;
        }
        // mark the last node, this is the end of our word
        // this is a marker of an end to a valid word
        current->marker = true;
    }
} trie;


int main() {
    trie t;
    t.insert("cake");
    t.insert("cakes");
    t.insert("cider");
    t.insert("civil");
    t.insert("cat");
    printf("%d\n", t.exact_match("cake"));
    printf("%d\n", t.exact_match("ca"));
    t.words_with_prefix("ca");
    return 0;
}
