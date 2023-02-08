#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *right, *left;
};

struct DLL {
    struct node *start, *end;
};

struct Iter {
    struct node *next, *prev;
    struct DLL *list;
};

struct DLL *new_DLL() {return malloc(sizeof(struct DLL));}

struct Iter *new_Iter(struct DLL *list) {
    if (list == NULL) return NULL;
    
    struct Iter *iter = malloc(sizeof(struct Iter));
    iter->next = list->start;
    iter->list = list;
    return iter;
}

struct node* getNode(struct DLL *list, int index) {
    if (list == NULL) printf("NullPointerException: Parameter passed as DLL is NULL\n\t@ function getNode(DLL, int, int): node\n");
    if (index == 0) return list->start;
    
    struct node *ptr;
    if (index>=0) ptr = list->start;
    else ptr = list->end;

    int i = 0;
    while (1) {
        if (index >= 0 && index <= i++) break;
        else if (index < 0 && index+1 >= i--) break;
        if (ptr == NULL) return NULL;
        if (index < 0) ptr = ptr->left;
        else ptr = ptr->right;
    }
    return ptr;
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
            if (prev == NULL) printf("InvalidIndexException: Unable to locate the node at index: %d\n\t@ function getNode(DLL, int, int): node\n", index-1);
            next = prev->right;
        } else {
            next = getNode(list, index+1);
            if (next == NULL) printf("InvalidIndexException: Unable to locate the node at index: %d\n\t@ function getNode(DLL, int, int): node\n", index-1);
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
    else list->end = prev;
    if (prev != NULL) prev->right = next;
    else list->start = next;

    int value = temp->value;
    free(temp);

    return value;
}

struct node* nextNode(struct Iter *iter) {
    if (iter == NULL) printf("NullPointerException: Parameter passed as Iter is NULL\n\t@ function nextNode(Iter): node\n");
    
    struct node *temp = iter->next;
    if (iter->next != NULL) {
        iter->prev = iter->next;
        iter->next = temp->right;
    }
    return temp;
}

struct node* prevNode(struct Iter *iter) {
    if (iter == NULL) printf("NullPointerException: Parameter passed as Iter is NULL\n\t@ function prevNode(Iter): node\n");
    
    struct node *temp = iter->prev;
    if (iter->prev != NULL) {
        iter->next = iter->prev;
        iter->prev = temp->left;
    }
    return temp;
}

int hasNextNode(struct Iter *iter) { 
    if (iter == NULL) printf("NullPointerException: Parameter passed as Iter is NULL\n\t@ function hasNextNode(Iter): int\n");
    
    return iter->next != NULL;
}

int hasPrevNode(struct Iter *iter) {
    if (iter == NULL) printf("NullPointerException: Parameter passed as Iter is NULL\n\t@ function hasPrevNode(Iter): int\n");
    
    return iter->prev != NULL;
}

void resetIterToStart(struct Iter *iter) {
    if (iter == NULL) printf("NullPointerException: Parameter passed as Iter is NULL\n\t@ function resetIterToStart(Iter): void\n");
    
    iter->next = iter->list->start;
    iter->prev = NULL;
}

void resetIterToEnd(struct Iter *iter) {
    if (iter == NULL) printf("NullPointerException: Parameter passed as Iter is NULL\n\t@ function resetIterToEnd(Iter): void\n");
    
    iter->prev = iter->list->end;
    iter->next = NULL;
}

int get(struct DLL *list, int index) {
    if (list == NULL) printf("NullPointerException: Parameter passed as DLL is NULL\n\t@ function get(DLL, int): int\n");

    struct node *ptr = getNode(list, index);
    if (ptr == NULL) printf("InvalidIndexException: Unable to locate the node at index: %d\n\t@ function set(DLL, int): int\n", index);
    return ptr->value;
}

void set(struct DLL *list, int index, int value) {
    if (list == NULL) printf("NullPointerException: Parameter passed as DLL is NULL\n\t@ function set(DLL, int, int): void\n");
    
    struct node *ptr = getNode(list, index);
    if (ptr == NULL) printf("InvalidIndexException: Unable to locate the node at index: %d\n\t@ function set(DLL, int, int): void\n", index);
    ptr->value = value;
}

int length(struct DLL *list) {
    if (list == NULL) printf("NullPointerException: Parameter passed as DLL is NULL\n\t@ function length(DLL): int\n");
    
    struct Iter *iter = new_Iter(list);
    int length = 0;
    while (nextNode(iter) != NULL) length++;
    return length;
}

void main() {
    struct DLL *linked = new_DLL();
    struct Iter *iter = new_Iter(linked);

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
        if (inp < 4) {
            if (inp == 1) index = 0;
            else if (inp == 3) index = -1;
            else {
                printf("Enter the index: ");
                scanf("%d", &index);
            }

            printf("Enter the value: ");
            scanf("%d", &value);

            insert(linked, index, value);
        } else if (inp < 7) {
            if (inp == 4) index = 0;
            else if (inp == 6) index = -1;
            else {
                printf("Enter the index: ");
                scanf("%d", &index);
            }

            printf("Value deleted: %d\n", delete(linked, index));
        } else if (inp == 7) {
            printf("Enter the index: ");
            scanf("%d", &index);

            printf("The value is %d\n", get(linked, index));
        } else if (inp == 8) {
            printf("Enter the index: ");
            scanf("%d", &index);

            printf("Enter the value: ");
            scanf("%d", &value);

            set(linked, index, value);
        } else if (inp == 9) printf("The length of the linked list is %d\n", length(linked));
        else break;

        printf("List:\t");
        resetIterToStart(iter);
        while (hasNextNode(iter)) printf("%d\t", nextNode(iter)->value);
        printf("\n");
    }
}
