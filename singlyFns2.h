#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node *link;
};

struct LinkedList {
    struct node *head;
};

struct LinkedList* new_LinkedList() {
    return malloc(sizeof(struct LinkedList));
}

struct Iterator {
    struct node *ptr, **head;
};

struct Iterator* new_Iterator(struct LinkedList* list) {
    if (list == NULL) return NULL;
    struct Iterator* iter = malloc(sizeof(struct Iterator));
    iter->ptr = list->head;
    iter->head = &(list->head);
    return iter;
}

int hasNextNode(struct Iterator* iter) {
    if (iter == NULL) return 0;
    return iter->ptr != NULL;
}

struct node* nextNode(struct Iterator* iter) {
    if (iter == NULL) return NULL;
    struct node* temp = iter->ptr;
    if (temp != NULL) iter->ptr = temp->link;
    return temp;
}

void resetIter(struct Iterator* iter) {
    if (iter == NULL) return;
    iter->ptr = *(iter->head);
}

struct node* getNode(struct LinkedList* list, int index) {
    if (list == NULL) return NULL;

    if (index == 0) return list->head;
    
    struct node* ptr;
    struct Iterator* iter = new_Iterator(list);
    if (index == -1) while(hasNextNode(iter)) ptr = nextNode(iter);
    else if (index == -2) {
        if (list->head->link != NULL) while (1) {
            ptr = nextNode(iter);
            if (ptr->link->link == NULL) break;
        }
    } else {
        for (int i = 0; i <= index; i++) {
            if (hasNextNode(iter)) ptr = nextNode(iter);
            else {
                free(iter);
                return NULL;
            }
        }
    }

    free(iter);
    return ptr;
}

int insertNode(struct LinkedList* list, int index, struct node* temp) {
    if (list == NULL) return 1;

    if (index == 0) {
        temp->link = list->head;
        list->head = temp;
        return 0;
    }

    struct node* ptr;
    if (index == -1) ptr = getNode(list, -1);
    else if (index > 0) ptr = getNode(list, index-1); 
    else return 1;

    if (ptr == NULL) return 1;
    temp->link = ptr->link;
    ptr->link = temp;
    return 0;
}

int insert(struct LinkedList* list, int index, int value) {
    if (list == NULL) return 1;
    
    struct node* temp = malloc(sizeof(struct node));
    temp->value = value;

    int returnCode = insertNode(list, index, temp);
    if (returnCode == 1) free(temp);
    return returnCode;
}

int delete(struct LinkedList* list, int index, int* value) {
    if (list == NULL) return 1;

    struct node* temp;
    if (index == 0) {
        temp = list->head;
        list->head = temp->link;
    } else if (index > -2) {
        struct node* ptr = getNode(list, index-1);
        if (ptr == NULL) return 1;
        temp = ptr->link;
        ptr->link = temp->link;
    } else return 1;

    *value = temp->value;
    free(temp);
    return 0;
}

int get(struct LinkedList* list, int index, int* value) {
    if (list == NULL) return 1;

    struct node* ptr = getNode(list, index);
    if (ptr == NULL) return 1;

    *value = ptr->value;
    return 0;
}

int set(struct LinkedList* list, int index, int value) {
    if (list == NULL) return 1;

    struct node* ptr = getNode(list, index);
    if (ptr == NULL) return 1;

    ptr->value = value;
    return 0;
}

int length(struct LinkedList* list) {
    int length = 0;
    struct Iterator* iter = new_Iterator(list);
    while(nextNode(iter) != NULL) length++;
    free(iter);
    return length;
}

void clearLinkedList(struct LinkedList* list) {
    if (list == NULL) return;

    while (list->head != NULL) {
        struct node* ptr = list->head;
        list->head = ptr->link;
        free(ptr);
    }
}