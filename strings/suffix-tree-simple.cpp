//
//  SuffixTree using a simple Trie
//  source: cracking the coding interview
//

#include <iostream>
#include <unordered_map>
#include <list>
#include <vector>

class SuffixTreeNode {
public:
    char c;
    std::unordered_map<char, SuffixTreeNode*> *children; // a map of children pointers
    std::list<int> *indexes;
    SuffixTreeNode();
    void insert(std::string s, int index);
    std::list<int> search(std::string s);
};

class SuffixTree {
public:
    SuffixTreeNode *root;
    SuffixTree(std::string s);
};

SuffixTree:: SuffixTree(std::string s) {
    root = new SuffixTreeNode();
    for (int i = 0; i < s.length(); i++) {
        //printf("inserting %s with index %d\n", s.substr(i).c_str(), i);
        root->insert(s.substr(i), i);

    }
}

SuffixTreeNode::SuffixTreeNode() {
    children = new std::unordered_map<char, SuffixTreeNode*>();
    indexes = new std::list<int>();
}

void SuffixTreeNode::insert(std::string s, int index) {
    if (s.size() == 0) { return; }

    indexes->push_back(index);
    c = s[0];

    // create or find the child with that character
    SuffixTreeNode *child = NULL;
    if (children->count(c)) { // child already exists
        child = (*children)[c];
    } else {
        child = new SuffixTreeNode();
        (*children)[c] = child; // insert the child here
    }

    // remaining characters
    std::string remainder = s.substr(1);
    child->insert(remainder, index); // recurse to insert the remaining characters
}

std::list<int> SuffixTreeNode::search(std::string s) {
    if (s.size() == 0) { return *indexes; }
    else {
        char c = s[0];
        if (children->count(c)) {
            SuffixTreeNode *p = (*children)[c];
            return p->search(s.substr(1)); // search for the remaining characters
        }
    }
    return std::list<int>();
}

int main() {
    std::vector<std::string> strings = {"ba", "ana", "n"};
    SuffixTree *t = new SuffixTree("banaana");

    for (auto s = strings.begin(); s != strings.end(); s++) {
        printf("searching for %s: ", s->c_str());
        std::list<int> indexes = t->root->search(*s);
        for (auto i = indexes.begin(); i != indexes.end(); i++) {
            printf("%d ", *i);
        }
        printf("\n");
    }
    return 0;
}
