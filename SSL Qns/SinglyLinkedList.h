#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *link;
};

struct SinglyLinkedList {
    struct node *head, *tail;
};

struct SinglyLinkedList* new_SinglyLinkedList() {
    return malloc(sizeof(struct SinglyLinkedList));
}

struct SinglyLinkedList_Iterator {
    struct node *ptr, **head;
};

struct SinglyLinkedList_Iterator* new_SinglyLinkedList_Iterator(struct SinglyLinkedList* list) {
    if (list == NULL) return NULL;
    struct SinglyLinkedList_Iterator* iter = malloc(sizeof(struct SinglyLinkedList_Iterator));
    iter->ptr = list->head;
    iter->head = &(list->head);
    return iter;
}

int SinglyLinkedList_Iterator_hasNextNode(struct SinglyLinkedList_Iterator* iter) {
    if (iter == NULL) return 0;
    return iter->ptr != NULL;
}

struct node* SinglyLinkedList_Iterator_nextNode(struct SinglyLinkedList_Iterator* iter) {
    if (iter == NULL) return NULL;
    struct node* temp = iter->ptr;
    if (temp != NULL) iter->ptr = temp->link;
    return temp;
}

void SinglyLinkedList_Iterator_reset(struct SinglyLinkedList_Iterator* iter) {
    if (iter == NULL) return;
    iter->ptr = *(iter->head);
}

struct node* SinglyLinkedList_getNode(struct SinglyLinkedList* list, int index) {
    if (list == NULL) return NULL;

    if (index < -2) return NULL;
    if (index == 0) return list->head;
    if (index == -1) return list->tail;
    
    struct node* ptr;
    struct SinglyLinkedList_Iterator* iter = new_SinglyLinkedList_Iterator(list);
    if (index == -2) {
        if (list->head->link != NULL) while (1) {
            ptr = SinglyLinkedList_Iterator_nextNode(iter);
            if (ptr->link->link == NULL) break;
        }
    } else {
        for (int i = 0; i <= index; i++) {
            if (SinglyLinkedList_Iterator_hasNextNode(iter)) ptr = SinglyLinkedList_Iterator_nextNode(iter);
            else {
                free(iter);
                return NULL;
            }
        }
    }

    free(iter);
    return ptr;
}

int SinglyLinkedList_insertNode(struct SinglyLinkedList* list, int index, struct node* temp) {
    if (list == NULL) return 1;

    if (index == 0 || index == -1 && list->head == NULL) {
        temp->link = list->head;
        list->head = temp;
        if (temp->link == NULL) list->tail = temp;
        return 0;
    }

    struct node* ptr;
    if (index == -1) ptr = SinglyLinkedList_getNode(list, -1);
    else if (index > 0) ptr = SinglyLinkedList_getNode(list, index-1); 
    else return 1;

    if (ptr == NULL) return 1;
    temp->link = ptr->link;
    ptr->link = temp;
    if (temp->link == NULL)  list->tail = temp;
    return 0;
}

int SinglyLinkedList_insert(struct SinglyLinkedList* list, int index, int value) {
    if (list == NULL) return 1;
    
    struct node* temp = malloc(sizeof(struct node));
    temp->value = value;

    int returnCode = SinglyLinkedList_insertNode(list, index, temp);
    if (returnCode == 1) free(temp);
    return returnCode;
}

int SinglyLinkedList_delete(struct SinglyLinkedList* list, int index, int* value) {
    if (list == NULL) return 1;

    struct node* temp;
    if (index == 0) {
        temp = list->head;
        list->head = temp->link;
        if (list->head == NULL) list->tail = NULL;
    } else if (index > -2) {
        struct node* ptr = SinglyLinkedList_getNode(list, index-1);
        if (ptr == NULL) return 1;
        temp = ptr->link;
        ptr->link = temp->link;
        if (ptr->link == NULL) list->tail = ptr;
    } else return 1;

    *value = temp->value;
    free(temp);
    return 0;
}

int SinglyLinkedList_get(struct SinglyLinkedList* list, int index, int* value) {
    if (list == NULL) return 1;

    struct node* ptr = SinglyLinkedList_getNode(list, index);
    if (ptr == NULL) return 1;

    *value = ptr->value;
    return 0;
}

int SinglyLinkedList_set(struct SinglyLinkedList* list, int index, int value) {
    if (list == NULL) return 1;

    struct node* ptr = SinglyLinkedList_getNode(list, index);
    if (ptr == NULL) return 1;

    ptr->value = value;
    return 0;
}

int SinglyLinkedList_length(struct SinglyLinkedList* list) {
    int length = 0;
    struct SinglyLinkedList_Iterator* iter = new_SinglyLinkedList_Iterator(list);
    while(SinglyLinkedList_Iterator_nextNode(iter) != NULL) length++;
    free(iter);
    return length;
}

void SinglyLinkedList_clear(struct SinglyLinkedList* list) {
    if (list == NULL) return;

    while (list->head != NULL) {
        struct node* ptr = list->head;
        list->head = ptr->link;
        free(ptr);
    }
}