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
    struct SinglyLinkedList *list, *odd, *even;
    list = new_SinglyLinkedList();
    odd = new_SinglyLinkedList();
    even = new_SinglyLinkedList();

    int max;
    printf("Enter the max count: ");
    scanf("%d", &max);

    for (int i = 0; i < max; i++) {
        printf("Enter the element[%d]: ", i);
        int value;
        scanf("%d", &value);

        SinglyLinkedList_insert(list, -1, value);
    }

    struct SinglyLinkedList_Iterator *iter = new_SinglyLinkedList_Iterator(list);
    while(SinglyLinkedList_Iterator_hasNextNode(iter)) {
        int value = SinglyLinkedList_Iterator_nextNode(iter)->value;
        if (value%2 == 0) SinglyLinkedList_insert(even, -1, value);
        else SinglyLinkedList_insert(odd, -1, value);
    }

    display(list, "Main: ");
    display(odd, "Odd: ");
    display(even, "Even: ");
}