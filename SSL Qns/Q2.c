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

    int length = SinglyLinkedList_length(list);
    printf("Length is %d\n", length);
}