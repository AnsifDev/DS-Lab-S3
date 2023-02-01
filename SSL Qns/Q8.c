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
    printf("Enter the max count: ");
    int max;
    scanf("%d", &max);
    
    struct SLL* list = new_SLL();
    for (int i = 0; i < max; i++) {
        printf("Enter the element[%d]: ", i);
        int value;
        scanf("%d", &value);

        SLL_insert(list, -1, value);
    }

    display(list, "List1: ");

    int index;
    printf("Enter the split index: ");
    scanf("%d", &index);

    struct SLL* list2 = new_SLL();

    struct node* prevNode = SLL_getNode(list, index);
    struct node* temp = prevNode->link;

    prevNode->link = NULL;
    list2->head = temp;

    list2->tail = list->tail;
    list->tail = prevNode;

    display(list, "List2: ");
    display(list2, "List3: ");
}