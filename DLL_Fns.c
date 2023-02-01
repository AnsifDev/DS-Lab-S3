#include<stdio.h>
#include<stdlib.h>

//Node declearation
struct node {
    int value;
    struct node *right, *left;
} *start, *end;

//getNode function returns the node from the requested index
struct node* getNode(int index) {

    if (index == 0) return start; //Index 0 indicates the first node
    if (index == -1) return end; //Index -1 indicates the last node
    if (index < 0) return NULL; //Index less than 0 is invalid except -1;

    //Code for returning node at the nth position
    struct node *ptr = start;
    for (int i = 0; i < index; i++) {
        if (ptr == NULL) return NULL;
        ptr = ptr->right;
    }
    return ptr;
}

//Insert function
//insert(0, v) means insert at the front
//insert(-1, v) means insert at the end
//insert(n, v) means insert at nth position
void insert(int index, int value) {
    if (index == 0) {
        //Pointer to point the next node;
        struct node *next = start;

        //Node created and value inserted
        struct node *temp = malloc(sizeof(struct node));
        temp->value = value;

        //Node insertion to the DLL
        if (start != NULL) {
            temp->left = next->left;
            next->left = temp;
        } else end = temp;

        temp->right = start;
        start = temp;
    } else if (index == -1) {
        //Pointer to point the previous node;
        struct node *prev = end;

        //Node created and value inserted
        struct node *temp = malloc(sizeof(struct node));
        temp->value = value;

        //Node insertion to the DLL
        if (end != NULL) {
            temp->right = prev->right;
            prev->right = temp;
        } else start = temp;

        temp->left = end;
        end = temp;
    } else {
        struct node *prev = getNode(index-1);
        if (prev == NULL) {
            printf("Invalid index error\n");
            return;
        }
        struct node *next = prev->right;

        struct node *temp = malloc(sizeof(struct node));
        temp->value = value;

        if (prev->right != NULL) {
            temp->left = next->left;
            next->left = temp;
        } else end = temp;

        temp->right = prev->right;
        prev->right = temp;
    }
}

//Delete function
//delete(0) means delete from the front
//delete(-1) means delete from the end
//delete(n) means delete from nth position
int delete(int index) {
    if (start == NULL) {
        printf("List is empty error\n");
        return 0;
    }
    
    struct node *temp;
    if (index == 0) {
        temp = start; //Target node retrival

        //Target node removal
        start = temp->right;
        if (start == NULL) end == NULL;
        else start->left = temp->left;
    } else if (index == -1) {
        temp = end; //Target node retrival

        //Target node removal
        end = temp->left;
        if (end == NULL) start = NULL;
        else end->right = temp->right;
    } else {
        temp = getNode(index); //Target node retrival
        if (temp == NULL) {
            printf("Invalid index error\n");
            return 0;
        }

        //Extracting previous node and next node
        struct node *prev = temp->left;
        struct node *next = temp->right;

        //Target node removal
        prev->right = next;
        if (next == NULL) end = prev;
        else next->left = prev;
    }

    int value = temp->value; //Value extracted
    free(temp); //Target node deleted
    return value; //Returns
}

void display() {
    struct node *ptr = start;
    while (ptr != NULL) {
        printf("%d\n", ptr->value);
        ptr = ptr->right;
    }
}

void main() {
    while(1) {
        printf(">> ");
        int input;
        scanf("%d", &input);

        if (input == 1) {
            printf("V: ");
            int value;
            scanf("%d", &value);
            printf("I: ");
            int index;
            scanf("%d", &index);
            insert(index, value);
        } else if (input == 2) {
            printf("I: ");
            int index;
            scanf("%d", &index);
            int value = delete(index);
            printf("Value: %d\n", value);
        } else if (input == 3) {
            display();
        }
    }
}
