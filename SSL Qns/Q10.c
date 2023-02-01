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
    struct SLL *list, *positive, *negative;
    list = new_SLL();
    positive = new_SLL();
    negative = new_SLL();

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
        if (value >= 0) SLL_insert(positive, -1, value);
        else SLL_insert(negative, -1, value);
    }

    display(list, "Main List: ");
    display(positive, "Positive: ");
    display(negative, "Negative: ");
}