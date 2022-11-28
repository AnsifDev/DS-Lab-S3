#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node *link
} *head, *nextPtr;

int insert(int value, int index) {
    if (index == 0) {
        struct node *temp = malloc(sizeof(struct node));
        temp->value = value;
        if (head != NULL) temp->link = head;
        head = temp;
    } else {
        if (index < -1) return 1;

        struct node *ptr = head, *temp;

        if (index > 0) {
            if (ptr == NULL) return 1;
            for (int i = 0; i != index-1; i++) {
                if (ptr->link == NULL) return 1;
                ptr = ptr->link;
            }
        }
        
        temp = malloc(sizeof(struct node));

        if (index == -1) {
            if (ptr == NULL) {
                head = temp;
                nextPtr = head;
                return 0;
            }
            while (ptr->link != NULL) ptr = ptr->link;
        }

        if (ptr->link != NULL) temp->link = ptr->link;
        temp->value = value;
        ptr->link = temp;
    }

    nextPtr = head;
    return 0;
}

int queryNode(struct node **temp, int index) {
    if (index == 0) {
        *temp = head;
    } else {
        struct node *ptr = head;
        if (index > 0) {
            if (ptr == NULL) return 1;
            for (int i = 0; i != index-1; i++) {
                if (ptr->link == NULL) return 1;
                ptr = ptr->link;
            }
        } else if (index == -1) {
            if (ptr == NULL) return 1;
            if (ptr->link != NULL) while (ptr->link->link != NULL) ptr = ptr->link;
        } else return 1;

        *temp = ptr->link;
        if (*temp == NULL) *temp = ptr;
        else ptr->link = (*temp)->link;
    }
    return 0;
}

int delete(int *value, int index) {
    struct node *temp;
    
    if (queryNode(&temp, index) != 0) return 1;
    if (index == 0) 
    if (temp == NULL) return 1;
    else head = temp->link;
    else if (head == temp) head = NULL;
    

    *value = temp->value;
    free(temp);

    nextPtr = head;
    return 0;
}

resetNodeIter() {
    nextPtr = head;
    return head;
}

struct node* nextNode() {
    struct node *temp = nextPtr;
    if (nextPtr != NULL) nextPtr = nextPtr->link;
    return temp;
}

int hasNextNode() {return nextPtr != NULL;}

void display() {
    printf("List:\t");
    resetNodeIter();
    while (hasNextNode()) printf("%d\t", nextNode()->value);
    printf("\n");
}

int get(int *value, int index) {
    struct node *temp;
    if (index > 0 && queryNode(&temp, index) == 0) *value = temp->value;
    else return -1;
    return 0;
}

void main() {
	int inp = 0;
	printf("Menu:\n    1. Insert at the begining\n    2. Insert at nth position\n");
    printf("    3. Insert at the end\n    4. Delete at the begining\n");
	printf("    5. Delete at nth position\n    6. Delete at the end\n    7. Exit\n");
	while(1) {
		printf(">> ");
		scanf("%d", &inp);

        if (inp < 1 || inp > 7) {
            printf("Error: Invalid Input!!!\n");
            continue;
        }
		
        if (inp < 4) {
            int value, index;

            printf("Enter the value: ");
            scanf("%d", &value);

            if (inp == 1) index = 0;
            else if (inp == 3) index = -1;
            else {
                printf("Enter the index: ");
                scanf("%d", &index);
            }

            if (insert(value, index) != 0) printf("Error: Invalid index\n");
        } else if (inp < 7) {
            int value, index;

            if (inp == 4) index = 0;
            else if (inp == 6) index = -1;
            else {
                printf("Enter the index: ");
                scanf("%d", &index);
            }

            if (delete(&value, index) == 0) printf("Value deleted: %d\n", value);
            else printf("Error: Invalid index\n");
        } else break;

        display();
	}
}
