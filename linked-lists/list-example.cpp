//
// Hashing by Chaining - another example
//

#include <iostream>
#include "list.h"

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
