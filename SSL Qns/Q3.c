#include "SinglyLinkedList.h"

void display(struct SLL* list) {
    printf("List: ");
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

    display(list);

    int removeable;
    printf("Enter the value to remove node: ");
    scanf("%d", &removeable);

    struct SLL_Iterator* iter = new_SLL_Iterator(list);
    for (int i = 0; SLL_Iterator_hasNextNode(iter); i++) {
        struct node* Node = SLL_Iterator_nextNode(iter);
        if (Node->value == removeable) {
            SLL_delete(list, i, &removeable);
            break;
        }
    }

    if (!SLL_Iterator_hasNextNode(iter)) printf("Value is not in the list\n");
    display(list);
}