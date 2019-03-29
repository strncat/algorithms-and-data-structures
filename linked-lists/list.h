//
//  list.h
//

#include <iostream>

class Node {
public:
    std::string data;
    Node *next;
    Node(std::string s);
};

class List {
public:
    Node *head;
    void printList();
    void insertAtFront(std::string s);
    void deleteFromList(std::string s);
    Node* search(std::string);
};
