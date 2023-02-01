#include "SinglyLinkedList.h"

void display(struct SLL* list, char* msg) {
    printf("%s", msg);
    struct SLL_Iterator* iter = new_SLL_Iterator(list);
    while(SLL_Iterator_hasNextNode(iter)) {
        int value = SLL_Iterator_nextNode(iter)->value;
        printf("\t%d", value);
    }
    printf("\n");
}

void main() {
    struct SLL *list, *odd, *even;
    list = new_SLL();
    odd = new_SLL();
    even = new_SLL();

    int max;
    printf("Enter the max count: ");
    scanf("%d", &max);

    for (int i = 0; i < max; i++) {
        printf("Enter the element[%d]: ", i);
        int value;
        scanf("%d", &value);

        SLL_insert(list, -1, value);
    }

    struct SLL_Iterator *iter = new_SLL_Iterator(list);
    while(SLL_Iterator_hasNextNode(iter)) {
        int value = SLL_Iterator_nextNode(iter)->value;
        if (value%2 == 0) SLL_insert(even, -1, value);
        else SLL_insert(odd, -1, value);
    }

    display(list, "Main: ");
    display(odd, "Odd: ");
    display(even, "Even: ");
}