#include "SinglyLinkedList.h"

void display(struct SLL* list, char* str) {
    printf("%s", str);
    for (struct node *ptr = list->head; ptr != NULL; ptr = ptr->link) {
        printf("\t%d", ptr->value);
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
    list2->head = temp; //Splited

    display(list, "List2: ");
    display(list2, "List3: ");
}