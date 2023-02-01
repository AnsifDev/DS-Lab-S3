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

    int number, count;
    printf("Enter the number to check the occurance: ");
    scanf("%d", &number);

    struct SLL_Iterator* iter = new_SLL_Iterator(list);
    while(SLL_Iterator_hasNextNode(iter))
        if (SLL_Iterator_nextNode(iter)->value == number) count++;
    
    printf("Count of %d in the list is %d\n", number, count);
}