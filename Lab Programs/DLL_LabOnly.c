#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *right, *left;
};

struct DLL {
    struct node *start, *end;
};

struct DLL *new_DLL() {return malloc(sizeof(struct DLL));}

struct node* getNode(struct DLL *list, int index) {
    if (list == NULL) printf("NullPointerException: Parameter passed as DLL is NULL\n\t@ function getNode(DLL, int, int): node\n");
    if (index == 0) return list->start;
    
    if (index>0) {
        struct node *ptr = list->start;
        for (int i = 0; i < index; i++) {
            if (ptr == NULL) return NULL;
            ptr = ptr->right;
        }
        return ptr;
    } else {
        struct node *ptr = list->end;
        index = -1-index;
        for (int i = 0; i < index; i++) {
            if (ptr == NULL) return NULL;
            ptr = ptr->left;
        }
        return ptr;
    }
}

void insert(struct DLL *list, int index, int value) {
    if (list == NULL) printf("NullPointerException: Parameter passed as DLL is NULL\n\t@ function insert(DLL, int, int): void\n");
    
    struct node *next, *prev, *temp = malloc(sizeof(struct node));
    temp->value = value;

    if (index == 0) {
        next = list->start;
        prev = NULL;
    } else if (index == -1) {
        next = NULL;
        prev = list->end;
    } else {
        if (index > 0) {
            prev = getNode(list, index-1);
            if (prev == NULL) printf("InvalidIndexException: Unable to locate the node at index: %d\n\t@ function getNode(DLL, int, int): node\n", index);
            next = prev->right;
        } else {
            next = getNode(list, index+1);
            if (next == NULL) printf("InvalidIndexException: Unable to locate the node at index: %d\n\t@ function getNode(DLL, int, int): node\n", -1-index);
            prev = next->left;
        } 
    }

    temp->right = next;
    temp->left = prev;
    if (next != NULL) next->left = temp;
    else list->end = temp;
    if (prev != NULL) prev->right = temp;
    else list->start = temp;
}

int delete(struct DLL *list, int index) {
    if (list == NULL) printf("NullPointerException: Parameter passed as DLL is NULL\n\t@ function delete(DLL, int): int\n");
    if (list->start == NULL) printf("UnderflowException: List is empty\n\t@ function delete(DLL, int): int\n");
    
    struct node *temp, *next, *prev;
    
    if (index == 0) temp = list->start;
    else if (index == -1) temp = list->end;
    else temp = getNode(list, index);
    
    
    next = temp->right;
    prev = temp->left;

    if (next != NULL) next->left = prev;
    else list->end == prev;
    if (prev != NULL) prev->right = next;
    else list->start == next;

    if (next != NULL) next->left = prev;
    else list->end = prev;
    if (prev != NULL) prev->right = next;
    else list->start = next;

    int value = temp->value;
    free(temp);

    return value;
}

int get(struct DLL *list, int index) {
    if (list == NULL) printf("NullPointerException: Parameter passed as DLL is NULL\n\t@ function get(DLL, int): int\n");

    return getNode(list, index)->value;
}

void set(struct DLL *list, int index, int value) {
    if (list == NULL) printf("NullPointerException: Parameter passed as DLL is NULL\n\t@ function set(DLL, int, int): void\n");
    
    getNode(list, index)->value = value;
}

int length(struct DLL *list) {
    if (list == NULL) printf("NullPointerException: Parameter passed as DLL is NULL\n\t@ function length(DLL): int\n");
    
    int length = 0;
    for (struct node *ptr = list->start; ptr != NULL; ptr = ptr->right) length++;
    return length;
}

void main() {
    struct DLL *linked = new_DLL();

    printf("Menu:\n    1.Insert At First\n    2.Insert At nth Position\n    3.Insert At End\n");
    printf("    4.Delete At First\n    5.Delete At nth Position\n    6.Delete At End\n");
    printf("    7.Set At nth position\n    8.Get At nth Position\n    9.Length\n    10.Exit\n");

    int inp;
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

        if (inp < 4) insert(linked, index, value);
        else if (inp < 7) printf("Value deleted: %d\n", delete(linked, index));
        else if (inp == 7) printf("The value is %d\n", get(linked, index));
        else if (inp == 8) set(linked, index, value);
        else if (inp == 9) printf("The length of the linked list is %d\n", length(linked));

        printf("List:\t");
        for (struct node *ptr = linked->start; ptr != NULL; ptr = ptr->right)
            printf("%d\t", ptr->value);
        printf("\n");
    }
}
