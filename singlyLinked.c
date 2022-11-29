#include <stdio.h>
#include <stdlib.h>

/*
    Singly Linked List Methods:
    1. int insert(int index, int value):
        Inserts the value to the speifed index
        Returns 0 if insertion is successfull
        Only exception here is Invalid Index
    2. int delete(int index, int *value):
        Removes the value from specified index and stores in the pointer 'value'
        Returns 0 if Deletion is sucessfull
        Only exception here is Invalid Index
    3. struct node* getNode(int index):
        Returns the specified node address
        Also returns NULL if Invalid Index is given or -2 passed as index while length is 1
        Returns last node address, if index given is -1
        Returns second last node address, if index given is -2
    4. int get(int index, *value):
        Stores the value at the index position to the pointing location in 'value'
        Returns 0 if retrival is sucessfull
        Returns non 0 if Invalid Index is given
    5. void resetNodeIter():
        Resets the node iterator's pointer to 0
        Node Iterator returns nodes from 0 to end when nextNode() method is called.
    6. struct node* nextNode():
        Returns the node address currently Node Iterator pointer points
        The pointer is incremented by 1 whenever this method is called
        Also returns NULL when there is no next node to return
    7. int hasNextNode():
        Returns 1 if there are more nodes available to return by the Node Iterator
        If there is no nodes left to return, Returns 0
*/

struct node {
    int value;
    struct node *link
} *head, *nextPtr;

int insert(int index, int value) {
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

struct node* getNode(int index) {
    if (index == 0) return head;
    else {
        struct node *ptr = head;
        if (ptr == NULL) return NULL;
        if (index > 0) {
            for (int i = 0; i != index; i++) {
                if (ptr == NULL) return NULL;
                ptr = ptr->link;
            }
        } else if (index == -1) while (ptr->link != NULL) ptr = ptr->link;
        else if (index == -2) {
            if (ptr->link == NULL) return NULL;
            while (ptr->link->link != NULL) ptr = ptr->link;
        } else return NULL;

        return ptr;
    }
}

int delete(int index, int *value) {
    struct node *temp, *ptr;

    if (head == NULL) return 1;
    
    if (index == 0 || index == -1 && head->link == NULL) {
        temp = head;
        head = temp->link;
    } else {
        ptr = getNode(index-1);
        temp = ptr->link;
        if (temp == NULL) return 1;
        ptr->link = temp->link;
    }
    
    *value = temp->value;
    free(temp);

    nextPtr = head;
    return 0;
}

void resetNodeIter() {nextPtr = head;}

struct node* nextNode() {
    struct node *temp = nextPtr;
    if (nextPtr != NULL) nextPtr = nextPtr->link;
    return temp;
}

int hasNextNode() {return nextPtr != NULL;}

int get(int index, int *value) {
    struct node *temp;

    if (index < 0) return 1;

    temp = getNode(index);
    if (temp == NULL) return 1;

    *value = temp->value; 
    return 0;
}

int length() {
    resetNodeIter();
    int i = 0;
    while (nextNode() != NULL) i++;
    return i;
}

void main() {
	int inp = 0;
	printf("Menu:\n    1. Insert at the begining\n    2. Insert at nth position\n");
    printf("    3. Insert at the end\n    4. Delete at the begining\n");
	printf("    5. Delete at nth position\n    6. Delete at the end\n");
    printf("    7. Get at the nth position\n    8. Length of the List\n    9. Exit\n\n");
	while(1) {
		printf(">> ");
		scanf("%d", &inp);

        if (inp < 1 || inp > 9) {
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

            if (insert(index, value) != 0) printf("Error: Invalid index\n");
        } else if (inp < 7) {
            if (inp == 4) index = 0;
            else if (inp == 6) index = -1;
            else {
                printf("Enter the index: ");
                scanf("%d", &index);
            }

            if (delete(index, &value) == 0) printf("Value deleted: %d\n", value);
            else printf("Error: Invalid index\n");
        } else if (inp == 7) {
            printf("Enter the index: ");
            scanf("%d", &index);

            if (get(index, &value) == 0) printf("The value is %d\n", value);
            else printf("Error: Invalid index\n");
        } else if (inp == 8) printf("The length of the linked list is %d\n", length());
        else break;

        printf("List:\t");
        resetNodeIter();
        while (hasNextNode()) printf("%d\t", nextNode()->value);
        printf("\n");
	}
}