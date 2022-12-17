#include "SinglyLinkedList.h"

void main() {
    printf("Enter the max count: ");
    int max;
    scanf("%d", &max);
    
    struct SinglyLinkedList* list = new_SinglyLinkedList();
    for (int i = 0; i < max; i++) {
        printf("Enter the element[%d]: ", i);
        int value;
        scanf("%d", &value);

        SinglyLinkedList_insert(list, -1, value);
    }

    int number, count;
    printf("Enter the number to check the occurance: ");
    scanf("%d", &number);

    struct SinglyLinkedList_Iterator* iter = new_SinglyLinkedList_Iterator(list);
    while(SinglyLinkedList_Iterator_hasNextNode(iter))
        if (SinglyLinkedList_Iterator_nextNode(iter)->value == number) count++;
    
    printf("Count of %d in the list is %d\n", number, count);
}