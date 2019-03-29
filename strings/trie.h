//
//  Trie
//

#include <iostream>

#define SIZE 26

class Node {
public:
    int value;
    Node *children[SIZE];
    Node() { // init
        for (int i = 0; i < SIZE; i++) {
            children[i] = NULL;
        }
    }
};

class Trie { // space is O(SIZE * key_length * count)
public:
    Node *root;
    int count;
    Trie() {
        root = new Node();
    }
    void insert(std::string word) {
        if (search(word)) { return; } // word already exist

        int length = (int) word.length();
        Node *current = root;

        this->count++; // increment word count

        for (int level = 0; level < length; level++) {
            int letterIndex = word[level] - 'a';
            if (!current->children[letterIndex]) {
                current->children[letterIndex] = new Node(); // insert each character at the appropriate level
            }
            current = current->children[letterIndex];
        }
        current->value = this->count; // mark the last node, this is the end of our word
        // this is a marker of an end to a valid word
    }

    int search(std::string word) { // O(m) where m is the length of key
        int m = (int) word.length();
        Node *current = root;

        for (int level = 0; level < m; level++) {
            int index = word[level] - 'a';

            if (!current->children[index]) { return 0; } // NOT FOUND
            
            current = current->children[index];
        }
        return (current != NULL && current->value);
    }
};
