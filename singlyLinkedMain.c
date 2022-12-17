#include "singlyFns2.h"

void main() {
    struct SinglyLinkedList* list1 = new_SinglyLinkedList();
    struct SinglyLinkedList_Iterator* iter = new_SinglyLinkedList_Iterator(list1);
    int inp = 0;
	printf("Menu:\n    1. Insert at the begining\n    2. Insert at nth position\n");
    printf("    3. Insert at the end\n    4. Delete at the begining\n");
	printf("    5. Delete at nth position\n    6. Delete at the end\n");
    printf("    7. Get at the nth position\n    8.Set at the nth position\n");
    printf("    9. Length of the List\n    10. Exit\n\n");
	while(1) {
		printf(">> ");
		scanf("%d", &inp);

        if (inp < 1 || inp > 10) {
            printf("Error: Invalid Input!!!\n");
            continue;
        }
		
        int value, index;
        if (inp < 4) {
            printf("Enter the value: ");
            scanf("%d", &value);

            if (inp == 1) index = 0;
            else if (inp == 3) index = -1;
            else {
                printf("Enter the index: ");
                scanf("%d", &index);
            }

            if (SinglyLinkedList_insert(list1, index, value) != 0) printf("Error: Invalid index\n");
        } else if (inp < 7) {
            if (inp == 4) index = 0;
            else if (inp == 6) index = -1;
            else {
                printf("Enter the index: ");
                scanf("%d", &index);
            }

            if (SinglyLinkedList_delete(list1, index, &value) == 0) printf("Value deleted: %d\n", value);
            else printf("Error: Invalid index\n");
        } else if (inp == 7) {
            printf("Enter the index: ");
            scanf("%d", &index);

            if (SinglyLinkedList_get(list1, index, &value) == 0) printf("The value is %d\n", value);
            else printf("Error: Invalid index\n");
        } else if (inp == 8) {
            printf("Enter the index: ");
            scanf("%d", &index);

            printf("Enter the value: ");
            scanf("%d", &value);

            if (SinglyLinkedList_set(list1, index, value) != 0) printf("Error: Invalid index\n");
        } else if (inp == 9) printf("The length of the linked list is %d\n", SinglyLinkedList_length(list1));
        else break;

        printf("List:\t");
        SinglyLinkedList_Iterator_reset(iter);
        while (SinglyLinkedList_Iterator_hasNextNode(iter)) printf("%d\t", SinglyLinkedList_Iterator_nextNode(iter)->value);
        printf("\n");
	}

    SinglyLinkedList_clear(list1);
    free(iter);
    free(list1);
}