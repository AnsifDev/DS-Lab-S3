#include "singlyFns3_LabOnly.h"

void main() {
    struct SLL* list1 = new_SLL();
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
        if (inp%3 == 2 || inp == 7) {
            printf("Enter the index: ");
            scanf("%d", &index);
        }
        else if (inp == 1 || inp == 4) index = 0;
        else if (inp == 3 || inp == 6) index = -1;

        if (inp < 4 || inp == 8) {
            printf("Enter the value: ");
            scanf("%d", &value);
        }

        if (inp < 4) SLL_insert(list1, index, value);
        else if (inp < 7) printf("Value deleted: %d\n", SLL_delete(list1, index));
        else if (inp == 7) printf("The value is %d\n", SLL_get(list1, index));
        else if (inp == 8) SLL_set(list1, index, value);
        else if (inp == 9) printf("The length of the linked list is %d\n", SLL_length(list1));
        else return;

        printf("List:\t");
        for (struct node *ptr = list1->head; ptr != NULL; ptr = ptr->link)
            printf("%d\t", ptr->value);
        printf("\n");
	}

    SLL_clear(list1);
}