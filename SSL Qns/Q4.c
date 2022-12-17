#include "SinglyLinkedList.h"

void display(struct SinglyLinkedList* list) {
    printf("List: ");
    struct SinglyLinkedList_Iterator* iter = new_SinglyLinkedList_Iterator(list);
    while(SinglyLinkedList_Iterator_hasNextNode(iter)) {
        int value = SinglyLinkedList_Iterator_nextNode(iter)->value;
        printf("\t%d", value);
    }
    printf("\n");
}

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

    display(list);

    int n, v;
    printf("Enter the index to replace node: ");
    scanf("%d", &n);
    printf("Enter a new value: ");
    scanf("%d", &v);

    struct node* prev = SinglyLinkedList_getNode(list, n-1);
    struct node* removeable = prev->link;
    struct node* temp = malloc(sizeof(struct node));

    temp->value = v;
    temp->link = removeable->link;
    prev->link = temp;
    free(removeable);

    display(list);
}