#include "SinglyLinkedList.h"

void display(struct SinglyLinkedList* list, char* msg) {
    printf("%s", msg);
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

    display(list, "List1: ");

    int index;
    printf("Enter the split index: ");
    scanf("%d", &index);

    struct SinglyLinkedList* list2 = new_SinglyLinkedList();

    struct node* prevNode = SinglyLinkedList_getNode(list, index);
    struct node* temp = prevNode->link;

    prevNode->link = NULL;
    list2->head = temp;

    list2->tail = list->tail;
    list->tail = prevNode;

    display(list, "List2: ");
    display(list2, "List3: ");
}