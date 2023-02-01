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
    printf("Enter the max count for list1: ");
    int max1;
    scanf("%d", &max1);
    
    struct SLL* list1 = new_SLL();
    for (int i = 0; i < max1; i++) {
        printf("Enter the element[%d]: ", i);
        int value;
        scanf("%d", &value);

        SLL_insert(list1, -1, value);
    }

    printf("Enter the max count for list2: ");
    int max2;
    scanf("%d", &max2);

    struct SLL* list2 = new_SLL();
    for (int i = 0; i < max2; i++) {
        printf("Enter the element[%d]: ", i);
        int value;
        scanf("%d", &value);

        SLL_insert(list2, -1, value);
    }

    display(list1, "List1: ");
    display(list2, "List2: ");

    struct node *list1_end, *list2_start;
    list1_end = SLL_getNode(list1, -1);
    list2_start = SLL_getNode(list2, 0);
    
    list1_end->link = list2_start;
    list1->tail = list2->tail;

    display(list1, "Merged List: ");
}