//
//  linked-list.c
//

#include "linked-list.h"
#include <stdlib.h>

void printList(list *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

list* insertAtTail(list *head, int d) {
    list *newNode = (list *) malloc(sizeof(list));
    newNode->data = d;
    newNode->next = NULL;

    if (head == NULL) { return newNode; }

    list *temp = head;
    while (temp->next) {
        temp = temp->next;
    }
    temp->next = newNode;
    return head;
}

list* insertAtFirst(list *head, int d) {
    list *newNode = (list *) malloc(sizeof(list));
    newNode->data = d;
    newNode->next = head;
    head = newNode;
    return newNode;
}

list* deleteFromList(list *head, int d) {
    if (head == NULL) { return NULL; }

    if (head->data == d) {  // first node is node to be deleted
        list *temp = head->next;
        free(head);
        return temp;
    }

    list *prev = head;
    while (prev->next != NULL) {
        if (prev->next->data == d) {
            list *temp = prev->next;
            prev->next = prev->next->next;
            free(temp);
            return head;
        }
        prev = prev->next;
    }
    return head;
}

list* search(list *head, int d) {
    if (head == NULL) { return NULL; }
    list *current;
    for (current = head; current != NULL; current = current->next) {
        if (current->data == d) {
            return current;
        }
    }
    return current;
}
