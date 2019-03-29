//
//  list.cpp
//

#include "list.h"

Node::Node(std::string s) {
    data = s;
}

void List::printList() {
    Node *temp = head;
    while (temp != NULL) {
        std::cout << temp->data;
        temp = temp->next;
    }
    std::cout << std::endl;
}

void List::insertAtFront(std::string s) {
    Node *newNode = new Node(s);
    newNode->next = head;
    head = newNode;
}

void List::deleteFromList(std::string d) {
    if (head == NULL) { return; }

    if (head->data == d) {  // first node is node to be deleted
        Node *temp = head->next;
        delete head; // free the allocation for the first node
        head = temp;
    }

    Node *prev = head;
    while (prev->next != NULL) {
        if (prev->next->data == d) {
            Node *temp = prev->next;
            prev->next = prev->next->next;
            delete temp;
            return;
        }
        prev = prev->next;
    }
}

Node* List::search(std::string d) {
    if (head == NULL) { return NULL; }
    Node *current;
    for (current = head; current != NULL; current = current->next) {
        if (current->data == d) {
            return current;
        }
    }
    return current;
};
