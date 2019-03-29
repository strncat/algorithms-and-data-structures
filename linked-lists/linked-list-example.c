//
// Linked Lists in C
//
#include <stdio.h>
#include <stdlib.h>
#include "linked-list.h"

int main() {
    list *head = NULL;
    head = insertAtFirst(head, 5);
    head = insertAtTail(head, 6);
    head = insertAtTail(head, 6);
    head = insertAtTail(head, 4);
    head = insertAtTail(head, 3);
    head = insertAtTail(head, 1);
    printList(head);

    printf("delete 6:\n");
    head = deleteFromList(head, 6);
    printList(head);
    printf("delete 4:\n");
    head = deleteFromList(head, 4);
    printList(head);
    printf("delete 1:\n");
    head = deleteFromList(head, 1);
    printList(head);

}
