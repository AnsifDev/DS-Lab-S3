#include "SinglyLinkedList.h"

void display(struct SinglyLinkedList* list) {
    printf("List: ");
    struct SinglyLinkedList_Iterator* iter = new_SinglyLinkedList_Iterator(list);
    while(SinglyLinkedList_Iterator_hasNextNode(iter)) {
        int value = SinglyLinkedList_Iterator_nextNode(iter)->value;
        printf("\t%d", value);
    }
    printf("\n");
}

void main() {
    printf("Enter the max count: ");
    int max;
    scanf("%d", &max);
    
    struct SinglyLinkedList* list = new_SinglyLinkedList();
    for (int i = 0; i < max; i++) {
        printf("Enter the element[%d]: ", i);
        int value;
        scanf("%d", &value);

        SinglyLinkedList_insert(list, -1, value);
    }

    display(list);

    int removeable;
    printf("Enter the value to remove node: ");
    scanf("%d", &removeable);

    struct SinglyLinkedList_Iterator* iter = new_SinglyLinkedList_Iterator(list);
    for (int i = 0; SinglyLinkedList_Iterator_hasNextNode(iter); i++) {
        struct node* Node = SinglyLinkedList_Iterator_nextNode(iter);
        if (Node->value == removeable) {
            SinglyLinkedList_delete(list, i, &removeable);
            break;
        }
    }

    if (!SinglyLinkedList_Iterator_hasNextNode(iter)) printf("Value is not in the list\n");
    display(list);
}