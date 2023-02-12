#include "SinglyLinkedList.h"

void display(struct SLL* list) {
    printf("List: ");
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

    display(list);

    int Num, index = 0;
    printf("Enter the number: ");
    scanf("%d", &Num);

    //Finding the location for the Num
    for (struct node *ptr = list->head; ptr != NULL; ptr = ptr->link)
        if (ptr->value <= Num) index++;
        else break;

    SLL_insert(list, index, Num);

    display(list);
}