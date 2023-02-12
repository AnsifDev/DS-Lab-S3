#include "SinglyLinkedList.h"

void display(struct SLL* list) {
    printf("List: ");
    for (struct node *ptr = list->head; ptr != NULL; ptr = ptr->link) {
        printf("\t%d", ptr->value);
    }
    printf("\n");
}

int deleteByValue(struct SLL* list, int value) {
    int i = 0;
    for (struct node *ptr = list->head; ptr != NULL; ptr = ptr->link) {
        if (ptr->value == value) {
            SLL_delete(list, i);
            return 1; //Indicates done
        }
        i++;
    }
    return 0; //Indicates failed to delete
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

    if (deleteByValue(list, removeable) == 0) printf("Value is not in the list\n");
    display(list);
}