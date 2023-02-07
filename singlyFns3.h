#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *link;
};

struct SLL {
    struct node *head, *tail;
};

struct SLL* new_SLL() {
    return malloc(sizeof(struct SLL));
}

struct SLL_Iter {
    struct node *ptr, **head;
};

struct SLL_Iter* new_SLL_Iter(struct SLL* list) {
    if (list == NULL) return NULL;

    struct SLL_Iter* iter = malloc(sizeof(struct SLL_Iter));
    iter->ptr = list->head;
    iter->head = &(list->head);
    return iter;
}

int SLL_Iter_hasNextNode(struct SLL_Iter* iter) {
    if (iter == NULL) printf("NullPointerException: Parameter passed as Iter is NULL\n\t@ function SLL_Iter_hasNextNode(Iter): int\n");
    
    return iter->ptr != NULL;
}

struct node* SLL_Iter_nextNode(struct SLL_Iter* iter) {
    if (iter == NULL) printf("NullPointerException: Parameter passed as Iter is NULL\n\t@ function SLL_Iter_nextNode(Iter): node\n");
    
    struct node* temp = iter->ptr;
    if (temp != NULL) iter->ptr = temp->link;
    return temp;
}

void SLL_Iter_reset(struct SLL_Iter* iter) {
    if (iter == NULL) printf("NullPointerException: Parameter passed as Iter is NULL\n\t@ function SLL_Iter_reset(Iter): void\n");
    
    iter->ptr = *(iter->head);
}

struct node* SLL_getNode(struct SLL* list, int index) {
    if (list == NULL) printf("NullPointerException: Parameter passed as SLL is NULL\n\t@ function SLL_getNode(SLL, int, int): node\n");
    
    if (index < -2) return NULL;
    
    struct node* ptr;
    int i = 0;

    if (list->head->link != NULL || index > -2) 
        for (ptr = list->head; 1; ptr = ptr->link) {
            if (index == -2 && ptr->link->link == NULL) break;
            else if (index == -1 && ptr->link == NULL) break;
            else if (index >= 0) 
                if (ptr == NULL) return NULL;
                else if (index <= i++) break;
        }
    return ptr;
}

int SLL_insert(struct SLL* list, int index, int value) {
    if (list == NULL) printf("NullPointerException: Parameter passed as SLL is NULL\n\t@ function SLL_insert(SLL, int, int): void\n");
    
    struct node *prev, *next, *temp = malloc(sizeof(struct node));
    temp->value = value;

    if (index == 0) {
        prev = NULL;
        next = list->head;
    } else {
        if (index == -1) prev = SLL_getNode(list, -1);
        else if (index > 0) prev = SLL_getNode(list, index-1); 
        if (prev == NULL) printf("InvalidIndexException: Unable to locate the node at index: %d\n\t@ function SLL_insert(SLL, int, int): void\n", index-1);
        next = prev->link;
    }
    
    temp->link = next;
    if (prev != NULL) prev->link = temp;
    else list->head = temp;
}

int SLL_delete(struct SLL* list, int index) {
    if (list == NULL) printf("NullPointerException: Parameter passed as SLL is NULL\n\t@ function SLL_delete(SLL, int): int\n");
    
    struct node *temp, *prev, *next;
    if (index == 0) {
        prev = NULL;
        temp = list->head;
    } else if (index > -2) {
        prev = SLL_getNode(list, index-1);
        if (prev == NULL) printf("InvalidIndexException: Unable to locate the node at index: %d\n\t@ function SLL_delete(SLL, int, int): void\n", index-1);
        temp = prev->link;
    }

    if (temp == NULL) printf("InvalidIndexException: Unable to locate the node at index: %d\n\t@ function SLL_delete(SLL, int, int): void\n", index);
    next = temp->link;
    
    if (prev != NULL) prev->link = next;
    else list->head = next;
    
    int value = temp->value;
    free(temp);
    return value;
}

int SLL_get(struct SLL* list, int index) {
    if (list == NULL) printf("NullPointerException: Parameter passed as SLL is NULL\n\t@ function SLL_get(SLL, int): int\n");
    
    struct node* ptr = SLL_getNode(list, index);
    if (ptr == NULL) printf("InvalidIndexException: Unable to locate the node at index: %d\n\t@ function SLL_get(SLL, int): int\n", index);

    return ptr->value;
}

void SLL_set(struct SLL* list, int index, int value) {
    if (list == NULL) printf("NullPointerException: Parameter passed as SLL is NULL\n\t@ function SLL_set(SLL, int, int): void\n");
    
    struct node* ptr = SLL_getNode(list, index);
    if (ptr == NULL) printf("InvalidIndexException: Unable to locate the node at index: %d\n\t@ function SLL_set(SLL, int, int): void\n", index);

    ptr->value = value;
}

int SLL_length(struct SLL* list) {
    if (list == NULL) printf("NullPointerException: Parameter passed as SLL is NULL\n\t@ function SLL_length(SLL): int\n");
    
    int length = 0;
    struct SLL_Iter* iter = new_SLL_Iter(list);
    while(SLL_Iter_nextNode(iter) != NULL) length++;
    free(iter);
    return length;
}

void SLL_clear(struct SLL* list) {
    if (list == NULL) printf("NullPointerException: Parameter passed as SLL is NULL\n\t@ function SLL_clear(SLL): void\n");
    
    while (list->head != NULL) {
        struct node* ptr = list->head;
        list->head = ptr->link;
        free(ptr);
    }
}