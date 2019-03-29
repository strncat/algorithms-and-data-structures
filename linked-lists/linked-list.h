//
//  linked-list.h
//

#include <stdio.h>

typedef struct list {
    int data;
    struct list *next;
} list;

void printList(list *head);
list *insertAtTail(list *head, int d);
list *insertAtFirst(list *head, int d);
list *deleteFromList(list *head, int d);
