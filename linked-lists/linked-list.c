//
//  linked-list.c
//

#include <iostream>
#include <stdlib.h>

typedef struct list {
    int data;
    struct list *next;
} list;


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
