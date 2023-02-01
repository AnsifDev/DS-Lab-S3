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

struct SLL_Iterator {
    struct node *ptr, **head;
};

struct SLL_Iterator* new_SLL_Iterator(struct SLL* list) {
    if (list == NULL) return NULL;
    struct SLL_Iterator* iter = malloc(sizeof(struct SLL_Iterator));
    iter->ptr = list->head;
    iter->head = &(list->head);
    return iter;
}

int SLL_Iterator_hasNextNode(struct SLL_Iterator* iter) {
    if (iter == NULL) return 0;
    return iter->ptr != NULL;
}

struct node* SLL_Iterator_nextNode(struct SLL_Iterator* iter) {
    if (iter == NULL) return NULL;
    struct node* temp = iter->ptr;
    if (temp != NULL) iter->ptr = temp->link;
    return temp;
}

void SLL_Iterator_reset(struct SLL_Iterator* iter) {
    if (iter == NULL) return;
    iter->ptr = *(iter->head);
}

struct node* SLL_getNode(struct SLL* list, int index) {
    if (list == NULL) return NULL;

    if (index < -2) return NULL;
    if (index == 0) return list->head;
    if (index == -1) return list->tail;
    
    struct node* ptr;
    struct SLL_Iterator* iter = new_SLL_Iterator(list);
    if (index == -2) {
        if (list->head->link != NULL) while (1) {
            ptr = SLL_Iterator_nextNode(iter);
            if (ptr->link->link == NULL) break;
        }
    } else {
        for (int i = 0; i <= index; i++) {
            if (SLL_Iterator_hasNextNode(iter)) ptr = SLL_Iterator_nextNode(iter);
            else {
                free(iter);
                return NULL;
            }
        }
    }

    free(iter);
    return ptr;
}

int SLL_insertNode(struct SLL* list, int index, struct node* temp) {
    if (list == NULL) return 1;

    if (index == 0 || index == -1 && list->head == NULL) {
        temp->link = list->head;
        list->head = temp;
        if (temp->link == NULL) list->tail = temp;
        return 0;
    }

    struct node* ptr;
    if (index == -1) ptr = SLL_getNode(list, -1);
    else if (index > 0) ptr = SLL_getNode(list, index-1); 
    else return 1;

    if (ptr == NULL) return 1;
    temp->link = ptr->link;
    ptr->link = temp;
    if (temp->link == NULL)  list->tail = temp;
    return 0;
}

int SLL_insert(struct SLL* list, int index, int value) {
    if (list == NULL) return 1;
    
    struct node* temp = malloc(sizeof(struct node));
    temp->value = value;

    int returnCode = SLL_insertNode(list, index, temp);
    if (returnCode == 1) free(temp);
    return returnCode;
}

int SLL_delete(struct SLL* list, int index, int* value) {
    if (list == NULL) return 1;

    struct node* temp;
    if (index == 0) {
        temp = list->head;
        list->head = temp->link;
        if (list->head == NULL) list->tail = NULL;
    } else if (index > -2) {
        struct node* ptr = SLL_getNode(list, index-1);
        if (ptr == NULL) return 1;
        temp = ptr->link;
        ptr->link = temp->link;
        if (ptr->link == NULL) list->tail = ptr;
    } else return 1;

    *value = temp->value;
    free(temp);
    return 0;
}

int SLL_get(struct SLL* list, int index, int* value) {
    if (list == NULL) return 1;

    struct node* ptr = SLL_getNode(list, index);
    if (ptr == NULL) return 1;

    *value = ptr->value;
    return 0;
}

int SLL_set(struct SLL* list, int index, int value) {
    if (list == NULL) return 1;

    struct node* ptr = SLL_getNode(list, index);
    if (ptr == NULL) return 1;

    ptr->value = value;
    return 0;
}

int SLL_length(struct SLL* list) {
    int length = 0;
    struct SLL_Iterator* iter = new_SLL_Iterator(list);
    while(SLL_Iterator_nextNode(iter) != NULL) length++;
    free(iter);
    return length;
}

void SLL_clear(struct SLL* list) {
    if (list == NULL) return;

    while (list->head != NULL) {
        struct node* ptr = list->head;
        list->head = ptr->link;
        free(ptr);
    }
}