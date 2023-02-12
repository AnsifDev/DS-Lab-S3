#include "SinglyLinkedList.h"

void display(struct SLL* list, char* str) {
    printf("%s", str);
    for (struct node *ptr = list->head; ptr != NULL; ptr = ptr->link) {
        printf("\t%d", ptr->value);
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
    for (struct node *ptr = list->head; ptr != NULL; ptr = ptr->link) {
        int value = ptr->value;
        if (value >= 0) SLL_insert(positive, -1, value);
        else SLL_insert(negative, -1, value);
    }

    display(list, "Main List: ");
    display(positive, "Positive: ");
    display(negative, "Negative: ");
}