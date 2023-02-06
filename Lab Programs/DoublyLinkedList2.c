#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *right, *left;
};

struct DLL {
    struct node *start, *end;
};

struct Iterator {
    struct node *next, *prev;
    struct DLL *list;
};

struct DLL *new_DLL() {return malloc(sizeof(struct DLL));}

struct Iterator *new_Iterator(struct DLL *list) {
    if (list == NULL) printf("Err: Parameter passed as DLL is NULL @ function new_Iterator(DLL): Iterator");

    struct Iterator *iter = malloc(sizeof(struct Iterator));
    iter->next = list->start;
    iter->list = list;
    return iter;
}

//Will not return a NULL value
struct node* getNode(struct DLL *list, int index) {
    if (list == NULL) printf("Err: Parameter passed as DLL is NULL @ function getNode(DLL, int, int): node");
    if (index == 0) return list->start;
    
    if (index>0) {
        struct node *ptr = list->start;
        for (int i = 0; i < index; i++) {
            if (ptr == NULL) printf("Err: Unable to locate a Node! No node found at index: %d @ function getNode(DLL, int, int): node", index);
            ptr = ptr->right;
        }
        return ptr;
    } else {
        struct node *ptr = list->end;
        index = (index*-1)-1;
        for (int i = 0; i < index; i++) {
            if (ptr == NULL) printf("Err: Unable to locate a Node! No node found at index: %d @ function getNode(DLL, int, int): node", (-1*index)+1);
            ptr = ptr->left;
        }
        return ptr;
    }
}

void insert(struct DLL *list, int index, int value) {
    if (list == NULL) printf("Err: Parameter passed as DLL is NULL @ function insert(DLL, int, int): void");
    
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
            next = prev->right;
        } else {
            next = getNode(list, index+1);
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
    if (list == NULL) printf("Err: NullPointerException! Parameter passed as DLL is NULL @ function delete(DLL, int): int");
    if (list->start == NULL) printf("Err: DLL Underflow! List is empty @ function delete(DLL, int): int");
    
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

    //while(1);
    int value = temp->value;
    free(temp);

    return value;
}

struct node* nextNode(struct Iterator *iter) {
    if (iter == NULL) printf("Err: NullPointerException! Parameter passed as Iterator is NULL @ function nextNode(Iterator): node");
    
    struct node *temp = iter->next;
    if (iter->next != NULL) {
        iter->prev = iter->next;
        iter->next = temp->right;
    }
    return temp;
}

struct node* prevNode(struct Iterator *iter) {
    if (iter == NULL) printf("Err: NullPointerException! Parameter passed as Iterator is NULL @ function prevNode(Iterator): node");
    
    struct node *temp = iter->prev;
    if (iter->prev != NULL) {
        iter->next = iter->prev;
        iter->prev = temp->left;
    }
    return temp;
}

int hasNextNode(struct Iterator *iter) { 
    if (iter == NULL) printf("Err: NullPointerException! Parameter passed as Iterator is NULL @ function hasNextNode(Iterator): int");
    
    return iter->next != NULL;
}

int hasPrevNode(struct Iterator *iter) {
    if (iter == NULL) printf("Err: NullPointerException! Parameter passed as Iterator is NULL @ function hasPrevNode(Iterator): int");
    
    return iter->prev != NULL;
}

void resetIterToStart(struct Iterator *iter) {
    if (iter == NULL) printf("Err: NullPointerException! Parameter passed as Iterator is NULL @ function resetIterToStart(Iterator): void");
    
    iter->next = iter->list->start;
    iter->prev = NULL;
}

void resetIterToEnd(struct Iterator *iter) {
    if (iter == NULL) printf("Err: NullPointerException! Parameter passed as Iterator is NULL @ function resetIterToEnd(Iterator): void");
    
    iter->prev = iter->list->end;
    iter->next = NULL;
}

int get(struct DLL *list, int index) {
    if (list == NULL) printf("Err: NullPointerException! Parameter passed as DLL is NULL @ function get(DLL, int): int");

    return getNode(list, index)->value;
}

void set(struct DLL *list, int index, int value) {
    if (list == NULL) printf("Err: NullPointerException! Parameter passed as DLL is NULL @ function set(DLL, int, int): void");
    
    getNode(list, index)->value = value;
}

int length(struct DLL *list) {
    if (list == NULL) printf("Err: NullPointerException! Parameter passed as DLL is NULL @ function length(DLL): int");
    
    struct Iterator *iter = new_Iterator(list);
    int length = 0;
    while (nextNode(iter) != NULL) length++;
    return length;
}

void main() {
    struct DLL *linked = new_DLL();
    struct Iterator *iter = new_Iterator(linked);

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
