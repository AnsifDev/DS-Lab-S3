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
    struct SinglyLinkedList *list, *positive, *negative;
    list = new_SinglyLinkedList();
    positive = new_SinglyLinkedList();
    negative = new_SinglyLinkedList();

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
        if (value >= 0) SinglyLinkedList_insert(positive, -1, value);
        else SinglyLinkedList_insert(negative, -1, value);
    }

    display(list, "Main List: ");
    display(positive, "Positive: ");
    display(negative, "Negative: ");
}