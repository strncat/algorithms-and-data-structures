//
//  list.cpp
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

int main() {

    List l;

    l.insertAtFront("nemo");
    l.insertAtFront(" ");
    l.insertAtFront("world");
    l.insertAtFront(" ");
    l.insertAtFront("hello");
    l.printList();

    printf("find nemo:\n");
    Node *s = l.search("nemo");
    if (s) { std::cout << s->data << std::endl; }

    printf("delete nemo:\n");
    l.deleteFromList("nemo");
    l.printList();
}
