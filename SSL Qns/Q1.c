#include "SinglyLinkedList.h"

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

    printf("List: ");
    struct SLL_Iterator* iter = new_SLL_Iterator(list);
    while(SLL_Iterator_hasNextNode(iter)) {
        int value = SLL_Iterator_nextNode(iter)->value;
        printf("\t%d", value);
    }
    printf("\n");
}